#include "src/http2/flow_control.h"
#include <limits.h>

static constexpr uint32_t kDefaultWindow = 65535;
static constexpr uint32_t kFrameSize = 1048576;
static constexpr const uint32_t kMaxWindowUpdateSize = 0x7fffffff;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(a, min, max) ((a) < (min) ? (min) : (a) > (max) ? (max) : (a))

ConnectionFlowControl::ConnectionFlowControl(uint32_t sent_init_window) {
    sent_init_window_ = sent_init_window;

    remote_window_ = kDefaultWindow;
    target_initial_window_size_ = kDefaultWindow;
    announced_window_ = kDefaultWindow;

    announced_stream_total_over_incoming_window_ = 0;
    max_frame_size_ = kFrameSize;
}

ConnectionFlowControl::~ConnectionFlowControl() {}

void ConnectionFlowControl::InitializeWindowSize() {
    const double target = 4194304;  // pow(2, 22);

    // Though initial window 'could' drop to 0, we keep the floor at 128
    target_initial_window_size_ = static_cast<int32_t> CLAMP(target, 128, INT32_MAX);

    // get bandwidth estimate and update max_frame accordingly.
    double bw_dbl = 0;

    // we target the max of BDP or bandwidth in microseconds.
    max_frame_size_ = static_cast<int32_t> CLAMP(
        MAX((int32_t)CLAMP(bw_dbl, 0, INT_MAX) / 1000, target_initial_window_size_), 16384, 16777215);
}

int64_t ConnectionFlowControl::TargetWindow() {
    return static_cast<uint32_t> MIN((int64_t)((1u << 31) - 1),
                                     announced_stream_total_over_incoming_window_ + target_initial_window_size_);
}

uint32_t ConnectionFlowControl::MaybeSendUpdate(bool writing_anyway) {
    const uint32_t target_announced_window = static_cast<uint32_t>(TargetWindow());
    if ((writing_anyway || announced_window_ <= target_announced_window / 2) &&
        announced_window_ != target_announced_window) {
        const uint32_t announce =
            static_cast<uint32_t> CLAMP(target_announced_window - announced_window_, 0, kMaxWindowUpdateSize);
        announced_window_ += announce;
        return announce;
    }
    return 0;
}

uint32_t ConnectionFlowControl::FlushWindowUpdates() {
    // CREATE WINDOW_UPDATE FRAME
    return MaybeSendUpdate(true);
}

void ConnectionFlowControl::StreamSentData(int64_t size) {
    remote_window_ -= size;
}

void ConnectionFlowControl::PreUpdateAnnouncedWindowOverIncomingWindow(int64_t delta) {
    if (delta > 0) {
        announced_stream_total_over_incoming_window_ -= delta;
    }
}

void ConnectionFlowControl::PostUpdateAnnouncedWindowOverIncomingWindow(int64_t delta) {
    if (delta > 0) {
        announced_stream_total_over_incoming_window_ += delta;
    }
}

bool ConnectionFlowControl::ValidateRecvData(int64_t incoming_frame_size) {
    if (incoming_frame_size > announced_window_) {
        return false;
    }
    return true;
}

void ConnectionFlowControl::CommitRecvData(int64_t incoming_frame_size) {
    announced_window_ -= incoming_frame_size;
}

bool ConnectionFlowControl::RecvData(int64_t incoming_frame_size) {
    if (!ValidateRecvData(incoming_frame_size)) return false;
    CommitRecvData(incoming_frame_size);
    return true;
}

void ConnectionFlowControl::RecvUpdate(uint32_t size) {
    remote_window_ += size;
}

int32_t ConnectionFlowControl::MaxFrameSize() const {
    return max_frame_size_;
}

uint32_t ConnectionFlowControl::SentInitWindow() const {
    return sent_init_window_;
}
// ---------------------------------------------------

StreamFlowControl::StreamFlowControl(uint32_t stream_id, ConnectionFlowControl *t)
    : stream_id_(stream_id)
    , tfc_(t) {

    remote_window_delta_ = 0;
    local_window_delta_ = 0;
    announced_window_delta_ = 0;
}

StreamFlowControl::~StreamFlowControl() {
    tfc_->PreUpdateAnnouncedWindowOverIncomingWindow(announced_window_delta_);
}

void StreamFlowControl::IncomingByteStreamUpdate(size_t max_size_hint, size_t have_already) {
    uint32_t sent_init_window = tfc_->SentInitWindow();  // HTTP2_SETTINGS_INITIAL_WINDOW_SIZE
    uint32_t max_recv_bytes;

    if (max_size_hint >= kMaxWindowUpdateSize - sent_init_window) {
        max_recv_bytes = kMaxWindowUpdateSize - sent_init_window;
    } else {
        max_recv_bytes = static_cast<uint32_t>(max_size_hint);
    }

    if (max_recv_bytes >= have_already) {
        max_recv_bytes -= static_cast<uint32_t>(have_already);
    } else {
        max_recv_bytes = 0;
    }

    if (local_window_delta_ < max_recv_bytes) {
        uint32_t add_max_recv_bytes = static_cast<uint32_t>(max_recv_bytes - local_window_delta_);
        local_window_delta_ += add_max_recv_bytes;
    }
}

void StreamFlowControl::SentData(int64_t outgoing_frame_size) {
    tfc_->StreamSentData(outgoing_frame_size);
    remote_window_delta_ -= outgoing_frame_size;
}

uint32_t StreamFlowControl::MaybeSendUpdate() {
    if (local_window_delta_ > announced_window_delta_) {
        uint32_t announce =
            static_cast<uint32_t> CLAMP(local_window_delta_ - announced_window_delta_, 0, kMaxWindowUpdateSize);
        UpdateAnnouncedWindowDelta(tfc_, announce);
        return announce;
    }
    return 0;
}

void StreamFlowControl::UpdateAnnouncedWindowDelta(ConnectionFlowControl *tfc, int64_t change) {
    tfc->PreUpdateAnnouncedWindowOverIncomingWindow(announced_window_delta_);
    announced_window_delta_ += change;
    tfc->PostUpdateAnnouncedWindowOverIncomingWindow(announced_window_delta_);
}

uint32_t StreamFlowControl::FlushWindowUpdates() {
    // CREATE WINDOW_UPDATE FRAME
    return MaybeSendUpdate();
}

bool StreamFlowControl::RecvData(int64_t incoming_frame_size) {
    if (!tfc_->ValidateRecvData(incoming_frame_size)) return false;
    UpdateAnnouncedWindowDelta(tfc_, -incoming_frame_size);
    local_window_delta_ -= incoming_frame_size;
    tfc_->CommitRecvData(incoming_frame_size);
    return true;
}

void StreamFlowControl::RecvUpdate(uint32_t size) {
    remote_window_delta_ += size;
}

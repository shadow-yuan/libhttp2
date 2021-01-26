#pragma once
#include <stddef.h>
#include <stdint.h>

class ConnectionFlowControl final {
public:
    explicit ConnectionFlowControl(uint32_t sent_init_window);
    ~ConnectionFlowControl();

    // Connection flow control initialization window size
    void InitializeWindowSize();

    // Returns the size of the WINDOW_UPDATE frame to be created
    uint32_t FlushWindowUpdates();

    // received a DATA frame
    bool RecvData(int64_t incoming_frame_size);

    // we have received a WINDOW_UPDATE frame for a connection
    void RecvUpdate(uint32_t size);

    int32_t MaxFrameSize() const;

private:
    uint32_t MaybeSendUpdate(bool writing_anyway);
    int64_t TargetWindow();

    // stream has been sent data
    void StreamSentData(int64_t size);

    void PreUpdateAnnouncedWindowOverIncomingWindow(int64_t delta);
    void PostUpdateAnnouncedWindowOverIncomingWindow(int64_t delta);
    bool ValidateRecvData(int64_t incoming_frame_size);
    void CommitRecvData(int64_t incoming_frame_size);

    uint32_t SentInitWindow() const;

private:
    uint32_t sent_init_window_;
    int64_t remote_window_;
    int64_t target_initial_window_size_;
    int64_t announced_window_;

    // send request +5, recv response -5
    int64_t announced_stream_total_over_incoming_window_;
    int32_t max_frame_size_;

    friend class StreamFlowControl;
};

class StreamFlowControl final {
public:
    StreamFlowControl(uint32_t stream_id, ConnectionFlowControl *t);
    ~StreamFlowControl();

    // GRPC_MESSAGE header 5 bytes
    void IncomingByteStreamUpdate(size_t max_size_hint, size_t have_already = 0);

    // send DATA frame (include grpc_message header 5 bytes)
    void SentData(int64_t outgoing_frame_size);

    // Returns the size of the WINDOW_UPDATE frame to be created
    uint32_t FlushWindowUpdates();

    // we have received data from the wire
    bool RecvData(int64_t incoming_frame_size);

    // we have received a WINDOW_UPDATE frame for a stream
    void RecvUpdate(uint32_t size);

private:
    uint32_t MaybeSendUpdate();

    void UpdateAnnouncedWindowDelta(ConnectionFlowControl *tfc, int64_t change);

    uint32_t stream_id_;
    ConnectionFlowControl *tfc_;

    int64_t remote_window_delta_;
    int64_t local_window_delta_;
    int64_t announced_window_delta_;
};

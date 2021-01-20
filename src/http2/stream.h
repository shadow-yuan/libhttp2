#pragma once

class http2_stream {
public:
    enum status {
        IDLE,
        RESERVED_LOCAL,
        RESERVED_REMOTE,
        OPEN,
        HALF_CLOSED_LOCAL,
        HALF_CLOSED_REMOTE,
        CLOSED,
    };

    http2_stream() = default;

    void send_pp();
    void recv_pp();
    void send_h();
    void recv_h();
    void send_r();
    void recv_r();
    void send_es();
    void recv_es();

private:
    status _cur_status = IDLE;
};

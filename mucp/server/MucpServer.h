#ifndef MUCP_SERVER_H
#define MUCP_SERVER_H

#include <cstdint>
#include <functional>
#include "../tcp/MucpTcpSocket.h"

class MucpServer {
public:
    using Handler = std::function<void(MucpTcpSocket&, const MucpPacket&)>;
    explicit MucpServer(uint16_t port);
    bool start(const Handler& h);

private:
    uint16_t port;
};

#endif

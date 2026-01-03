#ifndef MUCP_CLIENT_H
#define MUCP_CLIENT_H

#include "../tcp/MucpTcpSocket.h"

class MucpClient {
public:
    bool connectTo(const std::string& host, uint16_t port);
    bool send(const MucpPacket& p);
private:
    MucpTcpSocket sock;
};

#endif

#ifndef MUCP_TCP_SOCKET_H
#define MUCP_TCP_SOCKET_H

#include <string>
#include "../packet/MucpPacket.h"

class MucpTcpSocket {
public:
    MucpTcpSocket();
    ~MucpTcpSocket();

    bool connectTo(const std::string& host, uint16_t port);
    bool sendPacket(const MucpPacket& pkt);
    bool recvPacket(MucpPacket& out);

    static bool listenOn(uint16_t port, int& fd);
    static bool acceptClient(int listenFd, int& clientFd);

    void adopt(int fd);
    void close();

private:
    int sock;

    static bool sendAll(int fd, const uint8_t* d, size_t n);
    static bool recvAll(int fd, uint8_t* d, size_t n);
};

#endif

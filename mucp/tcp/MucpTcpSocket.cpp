#include "MucpTcpSocket.h"

#include <cstdint>

#include "../codec/MucpCodec.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib,"ws2_32")
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

MucpTcpSocket::MucpTcpSocket() : sock(-1) {}
MucpTcpSocket::~MucpTcpSocket() { close(); }

void MucpTcpSocket::close() {
#ifdef _WIN32
    if (sock != -1) closesocket((SOCKET)sock);
#else
    if (sock != -1) ::close(sock);
#endif
    sock = -1;
}

void MucpTcpSocket::adopt(int fd) {
    close();
    sock = fd;
}

bool MucpTcpSocket::connectTo(const std::string& host, uint16_t port) {
#ifdef _WIN32
    sock = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
    sock = socket(AF_INET, SOCK_STREAM, 0);
#endif
    if (sock == -1) return false;

    sockaddr_in a{};
    a.sin_family = AF_INET;
    a.sin_port = htons(port);

#ifdef _WIN32
    // InetPtonA
    if (InetPtonA(AF_INET, host.c_str(), &a.sin_addr) != 1) {
        close();
        return false;
    }
#else
    // inet_pton
    if (inet_pton(AF_INET, host.c_str(), &a.sin_addr) != 1) {
        close();
        return false;
    }
#endif

    return ::connect(sock, (sockaddr*)&a, sizeof(a)) == 0;
}

bool MucpTcpSocket::sendAll(int fd, const uint8_t* d, size_t n) {
    size_t s = 0;
    while (s < n) {
#ifdef _WIN32
        int r = send((SOCKET)fd, (const char*)d + s, (int)(n - s), 0);
#else
        ssize_t r = send(fd, d + s, n - s, 0);
#endif
        if (r <= 0) return false;
        s += (size_t)r;
    }
    return true;
}

bool MucpTcpSocket::recvAll(int fd, uint8_t* d, size_t n) {
    size_t r = 0;
    while (r < n) {
#ifdef _WIN32
        int k = recv((SOCKET)fd, (char*)d + r, (int)(n - r), 0);
#else
        ssize_t k = recv(fd, d + r, n - r, 0);
#endif
        if (k <= 0) return false;
        r += (size_t)k;
    }
    return true;
}

bool MucpTcpSocket::sendPacket(const MucpPacket& p) {
    auto b = MucpCodec::encode(p);
    return sendAll(sock, b.data(), b.size());
}

bool MucpTcpSocket::recvPacket(MucpPacket& p) {
    uint8_t h[16];
    if (!recvAll(sock, h, 16)) return false;
    if (!MucpCodec::decodeHeader(h, 16, p.header)) return false;

    p.payload.resize(p.header.payloadLen);
    return recvAll(sock, p.payload.data(), p.payload.size());
}

bool MucpTcpSocket::listenOn(uint16_t port, int& fd) {
#ifdef _WIN32
    fd = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
    fd = socket(AF_INET, SOCK_STREAM, 0);
#endif
    if (fd == -1) return false;

    sockaddr_in a{};
    a.sin_family = AF_INET;
    a.sin_port = htons(port);
    a.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(fd, (sockaddr*)&a, sizeof(a)) != 0) return false;
    return listen(fd, 16) == 0;
}

bool MucpTcpSocket::acceptClient(int l, int& c) {
#ifdef _WIN32
    SOCKET cs = accept((SOCKET)l, nullptr, nullptr);
    if (cs == INVALID_SOCKET) return false;
    c = (int)cs;
#else
    c = accept(l, nullptr, nullptr);
    if (c < 0) return false;
#endif
    return true;
}

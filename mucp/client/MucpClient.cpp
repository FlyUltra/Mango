#include "MucpClient.h"

bool MucpClient::connectTo(const std::string& h, uint16_t p) {
    return sock.connectTo(h,p);
}

bool MucpClient::send(const MucpPacket& p) {
    return sock.sendPacket(p);
}

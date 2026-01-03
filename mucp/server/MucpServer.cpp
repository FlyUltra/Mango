#include "MucpServer.h"
#include "../packet/MucpPacket.h"

MucpServer::MucpServer(uint16_t p):port(p){}

bool MucpServer::start(const Handler& h) {
    int lf;
    if(!MucpTcpSocket::listenOn(port,lf)) return false;
    int cf;
    if(!MucpTcpSocket::acceptClient(lf,cf)) return false;

    MucpTcpSocket c;
    c.adopt(cf);

    while(true){
        MucpPacket p;
        if(!c.recvPacket(p)) break;
        h(c,p);
    }
    return true;
}

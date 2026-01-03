#ifndef MUCP_PACKET_H
#define MUCP_PACKET_H

#include <vector>
#include <cstdint>
#include "../header/MucpHeader.h"

struct MucpPacket {
    MucpHeader header;
    std::vector<uint8_t> payload;
};

#endif

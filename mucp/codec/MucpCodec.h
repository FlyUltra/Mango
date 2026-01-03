#ifndef MUCP_CODEC_H
#define MUCP_CODEC_H

#include <vector>
#include <cstdint>
#include "../packet/MucpPacket.h"

class MucpCodec {
public:
    static std::vector<uint8_t> encode(const MucpPacket& packet);
    static bool decodeHeader(const uint8_t* data, size_t size, MucpHeader& out);

    static uint32_t toBE(uint32_t v);
    static uint32_t fromBE(uint32_t v);
};

#endif

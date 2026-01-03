#include "MucpCodec.h"
#include "../header/MucpHeader.h"

enum class MucpType : uint8_t;

static bool isLE() {
    uint16_t x = 1;
    return *(uint8_t*)&x == 1;
}

uint32_t MucpCodec::toBE(uint32_t v) {
    if (!isLE()) return v;
    return ((v & 0xFF) << 24) | ((v & 0xFF00) << 8) |
           ((v & 0xFF0000) >> 8) | ((v >> 24) & 0xFF);
}

uint32_t MucpCodec::fromBE(uint32_t v) {
    return toBE(v);
}

std::vector<uint8_t> MucpCodec::encode(const MucpPacket& p) {
    std::vector<uint8_t> out;
    out.reserve(16 + p.payload.size());

    out.insert(out.end(), p.header.magic, p.header.magic + 4);
    out.push_back(p.header.version);
    out.push_back((uint8_t)p.header.type);
    out.push_back(p.header.flags);
    out.push_back(p.header.reserved);

    uint32_t len = toBE((uint32_t)p.payload.size());
    uint32_t req = toBE(p.header.requestId);

    for (int i = 3; i >= 0; --i) out.push_back((len >> (i * 8)) & 0xFF);
    for (int i = 3; i >= 0; --i) out.push_back((req >> (i * 8)) & 0xFF);

    out.insert(out.end(), p.payload.begin(), p.payload.end());
    return out;
}

bool MucpCodec::decodeHeader(const uint8_t* d, size_t s, MucpHeader& h) {
    if (s < 16) return false;
    if (!(d[0]=='M'&&d[1]=='U'&&d[2]=='C'&&d[3]=='P')) return false;

    h.version = d[4];
    h.type = (MucpType)d[5];
    h.flags = d[6];
    h.reserved = d[7];

    uint32_t len = (d[8]<<24)|(d[9]<<16)|(d[10]<<8)|d[11];
    uint32_t req = (d[12]<<24)|(d[13]<<16)|(d[14]<<8)|d[15];

    h.payloadLen = fromBE(len);
    h.requestId = fromBE(req);
    return true;
}

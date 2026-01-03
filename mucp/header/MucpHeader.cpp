#ifndef MUCP_HEADER_H
#define MUCP_HEADER_H

#include <cstdint>
#include "../type/MucpType.h"

struct MucpHeader {
    uint8_t magic[4] { 'M','U','C','P' };

    uint8_t version { 1 };
    MucpType type { MucpType::Command };
    uint8_t flags { 0 };
    uint8_t reserved { 0 };

    uint32_t payloadLen { 0 };
    uint32_t requestId { 0 };
};

#endif

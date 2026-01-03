#ifndef MUCP_TYPE_H
#define MUCP_TYPE_H

#include <cstdint>

enum class MucpType : uint8_t {
    Command  = 0,
    Query    = 1,
    Event    = 2,
    Response = 3
};

#endif

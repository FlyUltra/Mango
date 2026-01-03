#ifndef MSON_BINARY_ENCODER_H
#define MSON_BINARY_ENCODER_H

#include <vector>
#include "../value/MsonValue.h"

class MsonBinaryEncoder {
public:
    static std::vector<uint8_t> encode(const MsonObject& object);

private:
    static void writeValue(std::vector<uint8_t>& out, const MsonValue& value);
    static void writeObject(std::vector<uint8_t>& out, const MsonObject& object);

    static void writeUInt32(std::vector<uint8_t>& out, uint32_t v);
    static void writeInt64(std::vector<uint8_t>& out, int64_t v);
};

#endif // MSON_BINARY_ENCODER_H

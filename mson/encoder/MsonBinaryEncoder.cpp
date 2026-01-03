#include "MsonBinaryEncoder.h"

enum : uint8_t {
    BIN_STRING = 0x01,
    BIN_INT    = 0x02,
    BIN_BOOL   = 0x03,
    BIN_OBJECT = 0x04
};

std::vector<uint8_t> MsonBinaryEncoder::encode(const MsonObject& object) {
    std::vector<uint8_t> out;
    writeObject(out, object);
    return out;
}

void MsonBinaryEncoder::writeObject(std::vector<uint8_t>& out, const MsonObject& object) {
    out.push_back(BIN_OBJECT);

    const auto& values = object.values();
    writeUInt32(out, static_cast<uint32_t>(values.size()));

    for (const auto& [key, value] : values) {
        // key jako string
        out.push_back(BIN_STRING);
        writeUInt32(out, static_cast<uint32_t>(key.size()));
        out.insert(out.end(), key.begin(), key.end());

        // value
        writeValue(out, value);
    }
}

void MsonBinaryEncoder::writeValue(std::vector<uint8_t>& out, const MsonValue& value) {
    switch (value.type) {
        case MsonType::String: {
            out.push_back(BIN_STRING);
            const auto& str = value.asString();
            writeUInt32(out, static_cast<uint32_t>(str.size()));
            out.insert(out.end(), str.begin(), str.end());
            break;
        }

        case MsonType::Int: {
            out.push_back(BIN_INT);
            writeInt64(out, value.asInt());
            break;
        }

        case MsonType::Bool: {
            out.push_back(BIN_BOOL);
            out.push_back(value.asBool() ? 1 : 0);
            break;
        }

        case MsonType::Object: {
            writeObject(out, value.asObject());
            break;
        }
    }
}

void MsonBinaryEncoder::writeUInt32(std::vector<uint8_t>& out, uint32_t v) {
    out.push_back((v >> 24) & 0xFF);
    out.push_back((v >> 16) & 0xFF);
    out.push_back((v >> 8) & 0xFF);
    out.push_back(v & 0xFF);
}

void MsonBinaryEncoder::writeInt64(std::vector<uint8_t>& out, int64_t v) {
    for (int i = 7; i >= 0; --i) {
        out.push_back((v >> (i * 8)) & 0xFF);
    }
}

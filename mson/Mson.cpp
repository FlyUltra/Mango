#include "Mson.h"
#include <sstream>

Mson::Mson() = default;

// ===== Builder =====

Mson& Mson::setString(const std::string& key, const std::string& value) {
    root.set(key, MsonValue(value));
    return *this;
}

Mson& Mson::setInt(const std::string& key, int64_t value) {
    root.set(key, MsonValue(value));
    return *this;
}

Mson& Mson::setBool(const std::string& key, bool value) {
    root.set(key, MsonValue(value));
    return *this;
}

Mson& Mson::setObject(const std::string& key, const Mson& object) {
    root.set(key, MsonValue(object.object()));
    return *this;
}

// ===== Access =====

const MsonObject& Mson::object() const {
    return root;
}

// ===== Serialization =====

std::string Mson::serializeValue(const MsonValue& value) {
    std::ostringstream out;

    switch (value.type) {
        case MsonType::String:
            out << "\"" << value.asString() << "\"";
            break;

        case MsonType::Int:
            out << value.asInt();
            break;

        case MsonType::Bool:
            out << (value.asBool() ? "true" : "false");
            break;

        case MsonType::Object: {
            out << "{";
            const auto& obj = value.asObject().values();

            bool first = true;
            for (const auto& [k, v] : obj) {
                if (!first) out << " ";
                first = false;

                out << "@" << k << ":" << serializeValue(v);
            }

            out << "}";
            break;
        }
    }

    return out.str();
}

std::string Mson::toString() const {
    std::ostringstream out;
    out << "{";

    const auto& values = root.values();
    bool first = true;

    for (const auto& [key, value] : values) {
        if (!first) out << " ";
        first = false;

        out << "@" << key << ":" << serializeValue(value);
    }

    out << "}";
    return out.str();
}

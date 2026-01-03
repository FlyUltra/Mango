#ifndef MSON_H
#define MSON_H

#include <string>
#include "object/MsonObject.h"
#include "value/MsonValue.h"

class Mson {
public:
    Mson();

    Mson& setString(const std::string& key, const std::string& value);
    Mson& setInt(const std::string& key, int64_t value);
    Mson& setBool(const std::string& key, bool value);
    Mson& setObject(const std::string& key, const Mson& object);

    const MsonObject& object() const;

    std::string toString() const;

private:
    MsonObject root;

    static std::string serializeValue(const MsonValue& value);
};

#endif

#ifndef MSONOBJECT_H
#define MSONOBJECT_H

#include <unordered_map>
#include <string>
#include "../value/MsonValue.h"

class MsonObject {
public:
    using Map = std::unordered_map<std::string, MsonValue>;

    void set(const std::string& key, const MsonValue& value);
    const MsonValue& get(const std::string& key) const;
    bool has(const std::string& key) const;

    const Map& values() const;

private:
    Map data;
};

#endif

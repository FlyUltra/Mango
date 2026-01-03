#include "MsonObject.h"

void MsonObject::set(const std::string& key, const MsonValue& value) {
data.insert_or_assign(key, value);
}

const MsonValue& MsonObject::get(const std::string& key) const {
    return data.at(key);
}

bool MsonObject::has(const std::string& key) const {
    return data.find(key) != data.end();
}

const MsonObject::Map& MsonObject::values() const {
    return data;
}

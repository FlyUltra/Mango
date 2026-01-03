#include "MsonValue.h"
#include <utility>

#include "../object/MsonObject.h"

MsonValue::MsonValue(const std::string& v)
    : type(MsonType::String), data(v) {}

MsonValue::MsonValue(int64_t v)
    : type(MsonType::Int), data(v) {}

MsonValue::MsonValue(bool v)
    : type(MsonType::Bool), data(v) {}

MsonValue::MsonValue(const MsonObject& v)
    : type(MsonType::Object), data(std::make_shared<MsonObject>(v)) {}

MsonValue::MsonValue(std::shared_ptr<MsonObject> v)
    : type(MsonType::Object), data(std::move(v)) {}

const std::string& MsonValue::asString() const {
    return std::get<std::string>(data);
}

int64_t MsonValue::asInt() const {
    return std::get<int64_t>(data);
}

bool MsonValue::asBool() const {
    return std::get<bool>(data);
}

const MsonObject& MsonValue::asObject() const {
    return *std::get<std::shared_ptr<MsonObject>>(data);
}

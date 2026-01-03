#ifndef MSONVALUE_H
#define MSONVALUE_H

#include <string>
#include <variant>
#include <memory>

class MsonObject;

enum class MsonType {
    String,
    Int,
    Bool,
    Object
};

struct MsonValue {
    MsonType type;

    std::variant<
        std::string,
        int64_t,
        bool,
        std::shared_ptr<MsonObject>
    > data;

    explicit MsonValue(const std::string& v);
    explicit MsonValue(int64_t v);
    explicit MsonValue(bool v);

    explicit MsonValue(const MsonObject& v);
    explicit MsonValue(std::shared_ptr<MsonObject> v);

    const std::string& asString() const;
    int64_t asInt() const;
    bool asBool() const;
    const MsonObject& asObject() const;
};

#endif

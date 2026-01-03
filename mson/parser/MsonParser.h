#ifndef MSONPARSER_H
#define MSONPARSER_H

#include <string>

#include "../value/MsonValue.h"


class MsonParser {
public:
    explicit MsonParser(const std::string& source);

    MsonValue parse();

private:
    const std::string& src;
    size_t pos;

    char peek() const;
    char consume();
    void skipWhitespace();
    void expect(char c);

    std::string parseIdentifier();
    std::string parseString();
    MsonValue parseValue();
    MsonValue parseObject();
};

#endif

#include "MsonParser.h"
#include "../object/MsonObject.h"
#include <stdexcept>
#include <cctype>

MsonParser::MsonParser(const std::string& source)
    : src(source), pos(0) {}

MsonValue MsonParser::parse() {
    skipWhitespace();
    return parseObject();
}

char MsonParser::peek() const {
    return pos < src.size() ? src[pos] : '\0';
}

char MsonParser::consume() {
    return pos < src.size() ? src[pos++] : '\0';
}

void MsonParser::skipWhitespace() {
    while (std::isspace(static_cast<unsigned char>(peek())))
        consume();
}

void MsonParser::expect(char c) {
    if (consume() != c)
        throw std::runtime_error("Unexpected character");
}

std::string MsonParser::parseIdentifier() {
    std::string id;
    while (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_') {
        id += consume();
    }
    return id;
}

std::string MsonParser::parseString() {
    expect('"');
    std::string value;
    while (peek() != '"') {
        value += consume();
    }
    expect('"');
    return value;
}

MsonValue MsonParser::parseValue() {
    skipWhitespace();

    if (peek() == '"')
        return MsonValue(parseString());

    if (std::isdigit(static_cast<unsigned char>(peek()))) {
        int64_t num = 0;
        while (std::isdigit(static_cast<unsigned char>(peek()))) {
            num = num * 10 + (consume() - '0');
        }
        return MsonValue(num);
    }

    if (src.compare(pos, 4, "true") == 0) {
        pos += 4;
        return MsonValue(true);
    }

    if (src.compare(pos, 5, "false") == 0) {
        pos += 5;
        return MsonValue(false);
    }

    if (peek() == '{')
        return parseObject();

    throw std::runtime_error("Invalid MSON value");
}

MsonValue MsonParser::parseObject() {
    expect('{');
    skipWhitespace();

    MsonObject obj;

    while (peek() == '@') {
        consume();
        std::string key = parseIdentifier();

        skipWhitespace();
        expect(':');
        skipWhitespace();

        obj.set(key, parseValue());
        skipWhitespace();
    }

    expect('}');
    return MsonValue(obj);
}

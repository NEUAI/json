//
// Created by 艾峥鹏 on 2018/11/3.
//

#include "json.h"

#include <string>

using namespace json;

number::number() = default;

number::number(const json::number &original) {
    value = original.value;
}

number::number(long double value) {
    this->value = value;
}

number::number(long long value) {
    this->value = std::to_string(value);
}

number::~number() = default;

number& number::operator=(const json::number &another) {
    if (this != &another) {
        value = another.value;
    }
    return *this;
}

long double number::to_decimal() const {
    return std::stold(value);
}

long long number::to_integer() const {
    return std::stoll(value);
}

std::string number::to_json_text() const {
    return value;
}

namespace json {
    std::ostream &operator<<(std::ostream &os, const number &num) {
        return os << num.to_json_text();
    }
}

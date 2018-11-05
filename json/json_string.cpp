//
// Created by 艾峥鹏 on 2018/11/3.
//

#include "json.h"

using namespace json;

string::string() = default;

string::string(const json::string &original) {
    value = original.value;
}

string::string(const std::string &value) {
    this->value = value;
}

string::~string() = default;

string& string::operator=(const json::string &another) {
    if (this != &another) {
        value = another.value;
    }
    return *this;
}

std::string string::to_string() const {
    return value;
}

std::string string::to_json_text() const {
    return "\"" + value + "\"";
}

namespace json {
    std::ostream &operator<<(std::ostream &os, const string &str) {
        return os << str.to_json_text();
    }
}

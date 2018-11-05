//
// Created by 艾峥鹏 on 2018/11/3.
//

#include "json.h"

using namespace json;

object::object() = default;

object::object(const json::object &original) {
    value = original.value;
}

object::~object() {
    for (auto &it : value) {
        delete it.second;
    }
}

object& object::operator=(const json::object &another) {
    if (this != &another) {
        value = another.value;
    }
    return *this;
}

type& object::operator[](const std::string &name) {
    return *value[name];
}

std::string object::to_json_text() const {
    std::string str = "{";
    bool is_first = true;
    for (auto &it : value) {
        if (is_first) {
            is_first = false;
        } else {
            str += ",";
        }
        str += ("\"" + it.first + "\":");
        str += it.second->to_json_text();
    }
    str += "}";
    return str;
}

size_t object::size() const {
    return value.size();
}

std::string object::dump() const {
    return to_json_text();
}

namespace json {
    std::ostream &operator<<(std::ostream &os, const object &obj) {
        return os << obj.to_json_text();
    }
}
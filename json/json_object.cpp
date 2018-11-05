#include "json.h"

#include <istream>

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
    std::istream &operator>>(std::istream &is, object &obj) {
        get_ws(is);

        if (is.get() != '{') {
            throw std::exception();
        }

        get_ws(is);

        if (is.peek() != '}') {
            int c;
            while (true) {
                string name;
                is >> name;

                get_ws(is);

                c = is.get();
                if (c != ':') {
                    throw std::exception();
                }

                get_ws(is);

                c = is.peek();
                if (c == '[') {
                    auto *t = new array();
                    is >> *t;
                    obj.value[name.to_string()] = t;
                } else if (c == 't' || c == 'f') {
                    auto *t = new boolean();
                    is >> *t;
                    obj.value[name.to_string()] = t;
                } else if (c == 'n') {
                    auto *t = new type();
                    is >> *t;
                    obj.value[name.to_string()] = t;
                } else if (c >= '0' && c <= '9') {
                    auto *t = new number();
                    is >> *t;
                    obj.value[name.to_string()] = t;
                } else if (c == '{') {
                    auto *t = new object();
                    is >> *t;
                    obj.value[name.to_string()] = t;
                } else if (c == '\"') {
                    auto *t = new string();
                    is >> *t;
                    obj.value[name.to_string()] = t;
                } else {
                    throw std::exception();
                }

                get_ws(is);

                c = is.peek();
                if (c == ',') {
                    is.get();
                    get_ws(is);
                    continue;
                } else if (c == '}') {
                    break;
                } else {
                    throw std::exception();
                }
            }
        }

        is.get();

        return is;
    }

    std::ostream &operator<<(std::ostream &os, const object &obj) {
        return os << obj.to_json_text();
    }
}
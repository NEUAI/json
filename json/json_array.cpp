//
// Created by 艾峥鹏 on 2018/11/3.
//

#include "json.h"

#include <istream>

using namespace json;

array::array() = default;

array::array(const array &original) {
    value = original.value;
}

array::~array() {
    for (type *element : value) {
        delete element;
    }
}

array &array::operator=(const array &another) {
    if (this != &another) {
        value = another.value;
    }
    return *this;
}

type &array::operator[](int index) {
    return *value[index];
}

std::string array::to_json_text() const {
    std::string str = "[";
    bool is_first = true;
    for (type *element : value) {
        if (is_first) {
            is_first = false;
        } else {
            str += ",";
        }
        str += element->to_json_text();
    }
    str += "]";
    return str;
}

size_t array::size() const {
    return value.size();
}

namespace json {
    std::istream &operator>>(std::istream &is, array &arr) {
        get_ws(is);

        if (is.get() != '[') {
            throw std::exception();
        }

        get_ws(is);

        if (is.peek() != ']') {
            int c;
            while (true) {
                c = is.peek();
                if (c == '[') {
                    auto *t = new array();
                    is >> *t;
                    arr.value.push_back(t);
                } else if (c == 't' || c == 'f') {
                    auto *t = new boolean();
                    is >> *t;
                    arr.value.push_back(t);
                } else if (c == 'n') {
                    auto *t = new type();
                    is >> *t;
                    arr.value.push_back(t);
                } else if (c >= '0' && c <= '9') {
                    auto *t = new number();
                    is >> *t;
                    arr.value.push_back(t);
                } else if (c == '{') {
                    auto *t = new object();
                    is >> *t;
                    arr.value.push_back(t);
                } else if (c == '\"') {
                    auto *t = new string();
                    is >> *t;
                    arr.value.push_back(t);
                } else {
                    throw std::exception();
                }

                get_ws(is);

                c = is.peek();
                if (c == ',') {
                    is.get();
                    get_ws(is);
                    continue;
                } else if (c == ']') {
                    break;
                } else {
                    throw std::exception();
                }
            }
        }

        is.get();

        return is;
    }

    std::ostream &operator<<(std::ostream &os, const array &arr) {
        return os << arr.to_json_text();
    }
}

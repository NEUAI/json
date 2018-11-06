#include "json.h"

#include <istream>

using namespace json;

boolean::boolean() {
    value = false;
}

boolean::boolean(const json::boolean &original) {
    value = original.value;
}

boolean::boolean(bool value) {
    this->value = value;
}

boolean::~boolean() = default;

boolean &boolean::operator=(const boolean &another) {
    if (this != &another) {
        value = another.value;
    }
    return *this;
}

bool boolean::to_boolean() const {
    return value;
}

std::string boolean::to_json_text() const {
    return value? "true" : "false";
}

namespace json {
    std::istream &operator>>(std::istream &is, boolean &b) {
        get_ws(is);

        int c = is.get();
        if (c == 't') {

            if (is.get() != 'r' || is.get() != 'u' || is.get() != 'e') {
                throw std::exception();
            }
            b.value = true;
        } else if (c == 'f') {
            if (is.get() != 'a' || is.get() != 'l' || is.get() != 's' || is.get() != 'e') {
                throw std::exception();
            }
            b.value = false;
        } else {
            throw std::exception();
        }

        return is;
    }

    std::ostream &operator<<(std::ostream &os, const boolean &b) {
        return os << b.to_json_text();
    }
}

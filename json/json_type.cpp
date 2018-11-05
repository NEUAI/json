#include "json.h"

#include <istream>

using namespace json;

type::type() = default;

type::~type() = default;

type &type::operator[](int index) {
    throw std::exception();
}

type &type::operator[](const std::string &name) {
    throw std::exception();
}

bool type::to_boolean() const {
    throw std::exception();
}

long double type::to_decimal() const {
    throw std::exception();
}

long long type::to_integer() const {
    throw std::exception();
}

std::string type::to_string() const {
    throw std::exception();
}

std::string type::to_json_text() const {
    return "null";
}

size_t type::size() const {
    throw std::exception();
}

namespace json {
    std::istream &operator>>(std::istream &is, type &t) {
        get_ws(is);

        if (is.get() != 'n' || is.get() != 'u' || is.get() != 'l' || is.get() != 'l') {
            throw std::exception();
        }

        return is;
    }

    std::ostream &operator<<(std::ostream &os, const type &t) {
        return os << t.to_json_text();
    }
}

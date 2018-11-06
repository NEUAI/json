#include "json.h"

#include <istream>
#include <string>

using namespace json;

number::number() = default;

number::number(const json::number &original) {
    value = original.value;
}

number::number(long double value) {
    this->value = std::to_string(value);
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
    std::istream &operator>>(std::istream &is, number &num) {
        get_ws(is);

        int c;
        char buffer[BUFSIZ];
        size_t size = 0;

        c = is.peek();
        if (c == '-') {
            if (size >= BUFSIZ) {
                throw std::exception();
            }
            buffer[size++] = (char)is.get();
        }

        c = is.peek();
        if (c == '0') {
            if (size >= BUFSIZ) {
                throw std::exception();
            }
            buffer[size++] = (char)is.get();
        } else if (c >= '1' && c <= '9') {
            while (c >= '0' && c <= '9') {
                if (size >= BUFSIZ) {
                    throw std::exception();
                }
                buffer[size++] = (char)is.get();
                c = is.peek();
            }
        } else {
            throw std::exception();
        }

        c = is.peek();
        if (c == '.') {
            if (size >= BUFSIZ) {
                throw std::exception();
            }
            buffer[size++] = (char)is.get();

            c = is.peek();
            if (c >= '0' && c <= '9') {
                while (c >= '0' && c <= '9') {
                    if (size >= BUFSIZ) {
                        throw std::exception();
                    }
                    buffer[size++] = (char)is.get();
                    c = is.peek();
                }
            } else {
                throw std::exception();
            }
        }

        c = is.peek();
        if (c == 'e' || c == 'E') {
            if (size >= BUFSIZ) {
                throw std::exception();
            }
            buffer[size++] = (char)is.get();

            c = is.peek();
            if (c == '+' || c == '-') {
                if (size >= BUFSIZ) {
                    throw std::exception();
                }
                buffer[size++] = (char)is.get();
                c = is.peek();
            }

            if (c >= '0' && c <= '9') {
                while (c >= '0' && c <= '9') {
                    if (size >= BUFSIZ) {
                        throw std::exception();
                    }
                    buffer[size++] = (char)is.get();
                    c = is.peek();
                }
            } else {
                throw std::exception();
            }
        }

        if (size >= BUFSIZ) {
            throw std::exception();
        }
        buffer[size] = '\0';

        num.value = buffer;
        return is;
    }

    std::ostream &operator<<(std::ostream &os, const number &num) {
        return os << num.to_json_text();
    }
}

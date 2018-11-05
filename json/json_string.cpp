#include "json.h"

#include <istream>

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
    std::istream &operator>>(std::istream &is, string &str) {
        get_ws(is);

        if (is.get() != '\"') {
            throw std::exception();
        }

        int c;
        char buffer[BUFSIZ];
        size_t size = 0;
        while (true) {
            c = is.get();

            if (c == '\"') {
                break;
            } else if (c == '\\') {
                if (size >= BUFSIZ) {
                    throw std::exception();
                }
                buffer[size++] = (char)c;

                c = is.get();
                if (c == '\"' || c == '\\' || c == '/' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't') {
                    if (size >= BUFSIZ) {
                        throw std::exception();
                    }
                    buffer[size++] = (char)c;
                } else if (c == 'u') {
                    if (size >= BUFSIZ) {
                        throw std::exception();
                    }
                    buffer[size++] = (char)c;
                    for (int i = 0; i < 4; i++) {
                        if (!isxdigit(c = is.get())) {
                            throw std::exception();
                        }
                        if (size >= BUFSIZ) {
                            throw std::exception();
                        }
                        buffer[size++] = (char)c;
                    }
                } else {
                    throw std::exception();
                }

            } else {
                if (size >= BUFSIZ) {
                    throw std::exception();
                }
                buffer[size++] = (char)c;
            }
        }

        if (size >= BUFSIZ) {
            throw std::exception();
        }
        buffer[size] = '\0';

        str.value = buffer;
        return is;
    }

    std::ostream &operator<<(std::ostream &os, const string &str) {
        return os << str.to_json_text();
    }
}

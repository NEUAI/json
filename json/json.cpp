#include "json.h"

#include <istream>
#include <sstream>

namespace json {
    void get_ws(std::istream &is) {
        while (isspace(is.peek()) && is.get());
    }

    object parse(const std::string &text) {
        object obj;
        std::stringstream(text) >> obj;
        return obj;
    }
}

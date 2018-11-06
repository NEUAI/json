# json

## Usage

```
g++ main.cpp json/json.h -ljson
```

## Example(s)

```
#include "json/json.h"

#include <iostream>

int main() {
    try {
        json::object obj;
        std::cin >> obj;
        std::cout << obj << std::endl;
    } catch (std::exception &) {
        std::cerr << "json: An exception was caught." << std::endl;
    }
    return 0;
}
```

## Reference(s)

* [IEEE.The JavaScript Object Notation (JSON) Data Interchange Format\[S\].RFC8259.](https://tools.ietf.org/pdf/rfc8259.pdf)

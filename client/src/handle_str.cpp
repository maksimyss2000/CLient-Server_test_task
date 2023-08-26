#include "handle_str.h"

constexpr auto MAX_SIZE = 64;
constexpr auto SUBSTR_FOR_REPLASE = "KB";

bool testInputStr(const std::string& str) {
    int found = str.find_first_not_of("0123456789");
    if (str.length() > MAX_SIZE || found != std::string::npos) {
        return false;
    }
    return true;
}

void replaceAllEven(std::string& str) {
    std::string substr_for_replase = SUBSTR_FOR_REPLASE;
    std::string chars_for_find = "02468";

    int found = 0;
    while ((found = str.find_first_of(chars_for_find, found)) != std::string::npos) {
            str.replace(found, 1, substr_for_replase);
    }
}

int calculateSumStr(const std::string& str) {
    int sum = 0;
    for (const char simbol : str) {
        if (isdigit(simbol)) {
            sum += simbol - '0';
        }
    }
    return sum;
}
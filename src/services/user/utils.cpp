#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "user/utils.h"



std::string generate_current_datetime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}
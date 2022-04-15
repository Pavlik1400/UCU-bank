#include <string>
#include <array>
#include <cstdlib>
#include <numeric>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "account/utils.h"


std::string generate_card_token() {
    std::array<char, 15> check_array{0};
    std::array<char, 17> card_num{0};

    for (int d = 14; d >= 0; d--) {
        card_num[d] = rand() % 10;
        check_array[d] = static_cast<char>((card_num[d] * (((d + 1) % 2) + 1)) % 9);
    }

    card_num[15] = static_cast<char>((std::accumulate(check_array.begin(), check_array.end(), 0) * 9) % 10);
    std::for_each(card_num.begin(), card_num.end(), [](char &x) { x += '0'; });
    card_num[16] = 0;
    return std::string{card_num.data()};
}

std::string generate_cvv() {
    std::array<char, 4> cvv{0};
    for (auto &number: cvv) {
        number = rand() % 10 + '0';
    }
    cvv[3] = 0;
    return std::string{cvv.data()};
}

std::string generate_current_datetime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}
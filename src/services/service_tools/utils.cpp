#include "utils.hpp"

#include <streambuf>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <random>


nlohmann::json load_json_config(const std::string &path) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error{"Json config path " + path + " doesn't exists"};
    }
    std::ifstream t(path);
    std::string content((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
    return nlohmann::json::parse(content);
}

//std::string cur_time_str() {
//    std::stringstream ss;
//    auto time = std::chrono::system_clock::now();
//    ss << time;
//    return ss.str();
//}

std::string cur_time_str() {
    // get current time
    auto now = std::chrono::system_clock::now();

    // get number of milliseconds for the current second
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = std::chrono::system_clock::to_time_t(now);

    // convert to broken time
    std::tm bt = *std::localtime(&timer);
    std::ostringstream oss;
    oss << std::put_time(&bt, "%F %T");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

std::string generate_current_datetime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}

std::string generate_random_string(size_t size) {
    std::uniform_int_distribution<int>d(' ', '~');

    std::random_device rd(("/dev/urandom"));
    std::vector<char> random_string{};
    random_string.reserve(size);
    for(size_t n = 0; n < size; ++n)
        random_string.push_back(static_cast<char>(d(rd)));
    return std::string{random_string.begin(), random_string.end()};
}
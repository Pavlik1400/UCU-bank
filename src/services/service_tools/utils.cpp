#include "utils.hpp"

#include <streambuf>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>


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
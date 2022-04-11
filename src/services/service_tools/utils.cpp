#include "utils.hpp"

#include <fstream>
#include <streambuf>
#include <sstream>
#include <filesystem>
#include <chrono>

nlohmann::json load_json_config(const std::string &path) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error{"Json config path " + path + " doesn't exists"};
    }
    std::ifstream t(path);
    std::string content((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
    return nlohmann::json::parse(content);
}

std::string cur_time_str() {
    std::stringstream ss;
    ss << std::chrono::system_clock::now();
    return ss.str();
}
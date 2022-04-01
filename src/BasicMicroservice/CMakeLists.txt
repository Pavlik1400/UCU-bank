find_package(RdKafka REQUIRED)
include(FindPackageHandleStandardArgs)
include(SelectLibraryConfigurations)

find_path(CPPKAFKA_INCLUDES NAMES cppkafka.h HINTS ${CURRENT_INSTALLED_DIR} PATH_SUFFIXES cppkafka)

find_library(CPPKAFKA_LIBRARY_DEBUG NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}" NO_DEFAULT_PATH REQUIRED)
find_library(CPPKAFKA_LIBRARY_RELEASE NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug" NO_DEFAULT_PATH REQUIRED)

select_library_configurations(CPPKAFKA)

find_package(serdepp CONFIG)
find_package(nlohmann_json CONFIG)
find_package(redis++ CONFIG REQUIRED)

add_executable(${EXE_07} include/BasicMicroservice.hpp include/MessageSerializer.hpp include/constants.hpp
        src/BasicMicroservice.cpp src/MessageSerializer.cpp src/main.cpp)

target_include_directories(${EXE_07} PRIVATE ${CPPKAFKA_INCLUDES}/.. ${Boost_INCLUDE_DIR} ${HIREDIS_HEADER}
        ${REDIS_PLUS_PLUS_HEADER} include)
target_link_libraries(${EXE_07} PRIVATE ${CPPKAFKA_LIBRARY} RdKafka::rdkafka++ serdepp::serdepp
        nlohmann_json::nlohmann_json redis++::redis++_static)

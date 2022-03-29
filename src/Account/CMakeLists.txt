find_package(RdKafka REQUIRED)
include(FindPackageHandleStandardArgs)
include(SelectLibraryConfigurations)

find_path(CPPKAFKA_INCLUDES NAMES cppkafka.h HINTS ${CURRENT_INSTALLED_DIR} PATH_SUFFIXES cppkafka)

find_library(CPPKAFKA_LIBRARY_DEBUG NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}" NO_DEFAULT_PATH REQUIRED)
find_library(CPPKAFKA_LIBRARY_RELEASE NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug" NO_DEFAULT_PATH REQUIRED)

select_library_configurations(CPPKAFKA)

find_package(serdepp CONFIG)
find_package(nlohmann_json CONFIG)
find_package(Boost REQUIRED)

find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)
set(SOURCES src/Account.cpp src/AccountMicroservice.cpp)
set(HEADERS include/Account.h include/AccountMicroservice.h ../BasicMicroservice/include/BasicMicroservice.hpp ../BasicMicroservice/include/constants.hpp include/constants.h)
add_executable(${EXE_08} ${SOURCES} ${HEADERS})
target_include_directories(${EXE_08} PRIVATE ${LIBMONGOCXX_INCLUDE_DIR})
target_include_directories(${EXE_08} PRIVATE ${LIBBSONCXX_INCLUDE_DIR})
target_include_directories(${EXE_08} PRIVATE ${CPPKAFKA_INCLUDES}/.. ${Boost_INCLUDE_DIR} include ../BasicMicroservice/include)
target_link_libraries(${EXE_08} mongo::mongocxx_static mongo::bsoncxx_static ${CPPKAFKA_LIBRARY} RdKafka::rdkafka++ serdepp::serdepp
        nlohmann_json::nlohmann_json)



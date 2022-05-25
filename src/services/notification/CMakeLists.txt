find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost COMPONENTS log REQUIRED)
find_package(aws-cpp-sdk-email REQUIRED)
find_package(ZLIB REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(RdKafka REQUIRED)
include(FindPackageHandleStandardArgs)
include(SelectLibraryConfigurations)

find_path(CPPKAFKA_INCLUDES NAMES cppkafka.h HINTS ${CURRENT_INSTALLED_DIR} PATH_SUFFIXES cppkafka)

find_library(CPPKAFKA_LIBRARY_DEBUG NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}" NO_DEFAULT_PATH REQUIRED)
find_library(CPPKAFKA_LIBRARY_RELEASE NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug" NO_DEFAULT_PATH REQUIRED)

select_library_configurations(CPPKAFKA)


set(SOURCES service.cpp email/MailSender.cpp)
set(HEADERS service.h email/MailSender.h)

add_executable(${NOTIFICATION} notification.cpp
        ${SOURCES} ${HEADERS}
        )
target_link_libraries(${NOTIFICATION} PRIVATE ${BASIC} ${CPPKAFKA_LIBRARY}
        RdKafka::rdkafka++
        nlohmann_json::nlohmann_json
        aws-cpp-sdk-email
        ${TOOLS}
        )

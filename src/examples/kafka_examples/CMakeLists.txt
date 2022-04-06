find_package(RdKafka REQUIRED)
include(FindPackageHandleStandardArgs)
include(SelectLibraryConfigurations)

find_path(CPPKAFKA_INCLUDES NAMES cppkafka.h HINTS ${CURRENT_INSTALLED_DIR} PATH_SUFFIXES cppkafka)

find_library(CPPKAFKA_LIBRARY_DEBUG NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}" NO_DEFAULT_PATH REQUIRED)
find_library(CPPKAFKA_LIBRARY_RELEASE NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug" NO_DEFAULT_PATH REQUIRED)

select_library_configurations(CPPKAFKA)

add_executable(${EXE_03}_producer src/kafka_base_producer.cpp)
target_include_directories(${EXE_03}_producer PRIVATE ${CPPKAFKA_INCLUDES}/..)
target_link_libraries(${EXE_03}_producer PRIVATE ${CPPKAFKA_LIBRARY} RdKafka::rdkafka++)

add_executable(${EXE_03}_consumer src/kafka_base_consumer.cpp)
target_include_directories(${EXE_03}_consumer PRIVATE ${CPPKAFKA_INCLUDES}/..)
target_link_libraries(${EXE_03}_consumer PRIVATE ${CPPKAFKA_LIBRARY} RdKafka::rdkafka++)

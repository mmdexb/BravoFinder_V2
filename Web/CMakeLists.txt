cmake_minimum_required(VERSION 3.1)
project(Web)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp handler.hpp bfhandler.hpp BfDataset.hpp)

include_directories(/usr/local/include/bfinder)


find_package(oatpp REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} oatpp::oatpp)
target_link_libraries(Web /usr/local/lib/libbfinder.so)

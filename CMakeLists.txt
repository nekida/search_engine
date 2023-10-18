cmake_minimum_required(VERSION 3.16)
project("search_engine" VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(search_engine main.cpp)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

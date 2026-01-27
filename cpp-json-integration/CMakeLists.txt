cmake_minimum_required(VERSION 3.16)
project(cpp-json-integration LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch header-only nlohmann/json from git (release tag)
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(cpp-json-integration main.cpp)

target_link_libraries(cpp-json-integration PRIVATE nlohmann_json::nlohmann_json)

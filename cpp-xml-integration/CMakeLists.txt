cmake_minimum_required(VERSION 3.15)
project(cpp-xml-integration)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch pugixml dependency
include(FetchContent)
FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG v1.14
)
FetchContent_MakeAvailable(pugixml)

# Create executable
add_executable(cpp-xml-integration main.cpp)

# Include pugixml headers
target_include_directories(cpp-xml-integration PRIVATE ${pugixml_SOURCE_DIR}/src)

# Link pugixml library
target_link_libraries(cpp-xml-integration PRIVATE pugixml)

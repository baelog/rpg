cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenSSL REQUIRED)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.15.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(Catch2)

set (CMAKE_CXX_FLAGS -fpermissive)

add_executable(server
    src/main.cpp
    src/network/packetStackHandler.cpp
    src/network/tools/MD5.cpp
)
target_compile_features(server PRIVATE cxx_std_17)
target_link_libraries(server PRIVATE SFML::Graphics OpenSSL::Crypto)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT server)

# test part

add_executable(test
    tests/socket/testPacket.cpp
    tests/socket/helper.cpp
    src/network/tools/MD5.cpp
    src/network/packetStackHandler.cpp
)

target_compile_features(test PRIVATE cxx_std_17)
target_link_libraries(test PRIVATE Catch2::Catch2WithMain OpenSSL::Crypto)


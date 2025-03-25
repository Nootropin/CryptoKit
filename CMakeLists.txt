cmake_minimum_required(VERSION 3.20.0)

project(CryptoKit)

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    # Find GTest only when tests are enabled
    find_package(GTest REQUIRED)

    # Define the test executable
    include_directories(include/)
    # file(GLOB INC_FILES "include/SHA256Hasher.hpp")
    file(GLOB TESTS_FILES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
    add_executable(runTests ${TESTS_FILES})

    # Link GTest with the test executable
    target_link_libraries(runTests GTest::GTest GTest::Main OpenSSL::Crypto)

    # Add test files
    target_sources(runTests PRIVATE src/SHA256Hasher.cpp src/SHA1Hasher.cpp src/SHA512Hasher.cpp)
    target_sources(runTests PRIVATE include/SHA256Hasher.hpp include/SHA1Hasher.hpp include/SHA512Hasher.hpp)
    # Add a custom target for running tests
    add_custom_target(tests
        COMMAND runTests
        DEPENDS runTests
        COMMENT "Run tests"
    )
endif()

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(OpenSSL REQUIRED)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB HDR_FILES "${CMAKE_SOURCE_DIR}/include/*.hpp")
add_executable(main ${SRC_FILES} ${HDR_FILES})
include_directories(include/)

target_link_libraries(main Qt6::Widgets OpenSSL::Crypto)
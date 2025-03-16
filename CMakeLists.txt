cmake_minimum_required(VERSION 3.20.0)

project(CryptoKit)

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
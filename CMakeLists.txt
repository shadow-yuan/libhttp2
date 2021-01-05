cmake_minimum_required(VERSION 3.10)
project(libhttp2)

add_executable(libhttp2-test "")

target_sources(libhttp2-test
    PRIVATE
    "${PROJECT_SOURCE_DIR}/test/main.cc"
)

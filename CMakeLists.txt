cmake_minimum_required(VERSION 3.10)
project(libhttp2)

set(PACKAGE_NAME          "libhttp2")
set(PACKAGE_VERSION       "1.0.0")

if(UNIX)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(LIBHTTP2_PLATFORM_LINUX ON)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(LIBHTTP2_PLATFORM_MAC ON)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "iOS")
        set(LIBHTTP2_PLATFORM_IOS ON)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
        set(LIBHTTP2_PLATFORM_ANDROID ON)
    else()
        set(LIBHTTP2_PLATFORM_POSIX ON)
    endif()
endif()
if(WIN32)
    set(LIBHTTP2_PLATFORM_WINDOWS ON)
endif()

if(LIBHTTP2_PLATFORM_MAC OR LIBHTTP2_PLATFORM_IOS)
    set(LIBHTTP2_BASE_LIBRARIES ${CMAKE_DL_LIBS} m pthread)
elseif(LIBHTTP2_PLATFORM_ANDROID)
    set(LIBHTTP2_BASE_LIBRARIES ${CMAKE_DL_LIBS} m)
elseif(UNIX)
    set(LIBHTTP2_BASE_LIBRARIES ${CMAKE_DL_LIBS} rt m pthread)
endif()

option(LIBHTTP2_BUILD_TESTS "Build tests" OFF)

add_library(http2 STATIC "")

set(HPACK_SOURCES
    "${PROJECT_SOURCE_DIR}/src/hpack/decode.cc"
    "${PROJECT_SOURCE_DIR}/src/hpack/dynamic_metadata.cc"
    "${PROJECT_SOURCE_DIR}/src/hpack/encode.cc"
    "${PROJECT_SOURCE_DIR}/src/hpack/hpack.cc"
    "${PROJECT_SOURCE_DIR}/src/hpack/huffman_data.cc"
    "${PROJECT_SOURCE_DIR}/src/hpack/huffman.cc"
    "${PROJECT_SOURCE_DIR}/src/hpack/static_metadata.cc"
)

set(HTTP2_SOURCES
    "${PROJECT_SOURCE_DIR}/src/http2/connection_setting.cc"
    "${PROJECT_SOURCE_DIR}/src/http2/connection.cc"
    "${PROJECT_SOURCE_DIR}/src/http2/frame.cc"
    "${PROJECT_SOURCE_DIR}/src/http2/parser.cc"
    "${PROJECT_SOURCE_DIR}/src/http2/stream.cc"
    "${PROJECT_SOURCE_DIR}/src/http2/transport.cc"
)

set(UTILS_SOURCES
    "${PROJECT_SOURCE_DIR}/src/utils/byte_convert.cc"
    "${PROJECT_SOURCE_DIR}/src/utils/mpscq.cc"
    "${PROJECT_SOURCE_DIR}/src/utils/murmur_hash.cc"
    "${PROJECT_SOURCE_DIR}/src/utils/slice_buffer.cc"
    "${PROJECT_SOURCE_DIR}/src/utils/slice.cc"
)

target_sources(http2
    PRIVATE
    "${PROJECT_SOURCE_DIR}/src/http2.cc"
    "${PROJECT_SOURCE_DIR}/src/init.cc"
    ${HPACK_SOURCES}
    ${HTTP2_SOURCES}
    ${UTILS_SOURCES}
)

target_include_directories(http2
    PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(http2
    PRIVATE
    ${LIBHTTP2_BASE_LIBRARIES}
)

if (LIBHTTP2_BUILD_TESTS)
    enable_testing()
    function(libhttp2_test test_file)
        get_filename_component(test_target_name "${test_file}" NAME_WE)
        add_executable("${test_target_name}" "")
        target_sources("${test_target_name}"
            PRIVATE
            "${PROJECT_SOURCE_DIR}/src/utils/testutil.cc"
            "${PROJECT_SOURCE_DIR}/src/utils/testutil.h"

            "${test_file}"
        )
        target_link_libraries("${test_target_name}" http2)

        add_test(NAME "${test_target_name}" COMMAND "${test_target_name}")
    endfunction(libhttp2_test)

    libhttp2_test("${PROJECT_SOURCE_DIR}/test/dynamic_table.cc")
    libhttp2_test("${PROJECT_SOURCE_DIR}/test/hpack_test.cc")
    libhttp2_test("${PROJECT_SOURCE_DIR}/test/huffman_test.cc")
    libhttp2_test("${PROJECT_SOURCE_DIR}/test/slice_test.cc")
    libhttp2_test("${PROJECT_SOURCE_DIR}/test/static_table_test.cc")

endif(LIBHTTP2_BUILD_TESTS)

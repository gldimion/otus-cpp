cmake_minimum_required(VERSION 3.20)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

option(WITH_TESTS "Build unit tests" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(ip_filter ip_filter.cpp)
add_library(ip_filter_lib ip.cpp)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

if(WITH_TESTS)
    find_package(GTest REQUIRED)
    include(GoogleTest)
    enable_testing()

    add_executable(test_ip test_ip.cpp)
    target_link_libraries(test_ip PRIVATE
        GTest::gtest_main
        ip_filter_lib
    )
    gtest_discover_tests(test_ip)

    # Reference checksum from the assignment
    add_test(NAME ip_filter_md5
        COMMAND sh -c "$<TARGET_FILE:ip_filter> < ${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv | md5sum | grep -q 24e7a7b2270daee89c64d3ca5fb3da1a"
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

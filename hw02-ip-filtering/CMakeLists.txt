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

configure_file(version.h.in version.h)

add_executable(ip_filter ip_filter.cpp)
add_library(ip_filter_lib lib.cpp)

target_include_directories(ip_filter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

if(WITH_TESTS)
    find_package(GTest REQUIRED)
    include(GoogleTest)
    enable_testing()

    add_executable(test_version test_version.cpp)
    target_link_libraries(test_version PRIVATE
        GTest::gtest_main
        ip_filter_lib
    )
    gtest_discover_tests(test_version)
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

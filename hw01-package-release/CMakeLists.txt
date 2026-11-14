cmake_minimum_required(VERSION 3.20)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})

option(WITH_TESTS "Build unit tests" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)

target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    helloworld
)

if(WITH_TESTS)
    find_package(GTest REQUIRED)
    include(GoogleTest)
    enable_testing()

    add_executable(test_version test_version.cpp)
    target_link_libraries(test_version PRIVATE
        GTest::gtest_main
        helloworld
    )
    gtest_discover_tests(test_version)
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

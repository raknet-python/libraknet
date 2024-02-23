cmake_minimum_required(VERSION 3.5)


project(raknet)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
    # tell ranlib to ignore empty compilation units
    set(CMAKE_C_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols <TARGET>")
    set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols <TARGET>")
    # prevents ar from invoking ranlib, let CMake do it
    set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qc -S <TARGET> <LINK_FLAGS> <OBJECTS>")
    set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qc -S <TARGET> <LINK_FLAGS> <OBJECTS>")
endif ()


IF (WIN32 AND NOT UNIX)
    list(APPEND RAKNET_LINK_LIBRARIES ws2_32.lib)
ELSE ()
    list(APPEND RAKNET_LINK_LIBRARIES pthread)
ENDIF ()

file(GLOB RAKNET_SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_library(raknet ${RAKNET_SOURCE_FILES})
target_include_directories(raknet PUBLIC include)
target_link_libraries(raknet ${RAKNET_LINK_LIBRARIES})


option(BUILD_TESTING "Enable the building of tests" OFF)
if (NOT BUILD_TESTING STREQUAL OFF)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(GLOB RAKNET_TEST_FILES CONFIGURE_DEPENDS "tests/*.cpp")
    add_executable(raknet_test ${RAKNET_TEST_FILES})
    target_link_libraries(raknet_test raknet GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(raknet_test)
endif ()

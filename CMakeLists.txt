cmake_minimum_required(VERSION 3.5)


project(raknet)


option(CODE_COVERAGE "Enable code coverage reporting" false)
if (NOT BUILD_TESTING STREQUAL OFF)
    enable_testing()

    if (CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g --coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --coverage")
    endif ()
endif ()


IF (WIN32 AND NOT UNIX)
    list(APPEND RAKNET_LINK_LIBRARIES ws2_32.lib)
ELSE ()
    list(APPEND RAKNET_LINK_LIBRARIES pthread)
ENDIF ()

if (APPLE)
    # tell ranlib to ignore empty compilation units
    set(CMAKE_C_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols <TARGET>")
    set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols <TARGET>")
    # prevents ar from invoking ranlib, let CMake do it
    set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qc -S <TARGET> <LINK_FLAGS> <OBJECTS>")
    set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qc -S <TARGET> <LINK_FLAGS> <OBJECTS>")
endif ()


file(GLOB RAKNET_SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_library(raknet ${RAKNET_SOURCE_FILES})
target_include_directories(raknet PUBLIC include)
target_link_libraries(raknet ${RAKNET_LINK_LIBRARIES})


file(GLOB RAKNET_TEST_FILES CONFIGURE_DEPENDS "tests/*.cpp")
add_executable(raknet_test ${RAKNET_TEST_FILES})
target_link_libraries(raknet_test raknet)
add_test(NAME raknet_test COMMAND raknet_test)

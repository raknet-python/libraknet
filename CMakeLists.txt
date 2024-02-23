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
    set(RAKNET_LIBRARY_LIBS ws2_32.lib)
ELSE ()
    set(RAKNET_LIBRARY_LIBS pthread)
ENDIF ()


file(GLOB_RECURSE RAKNET_SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_library(raknet ${RAKNET_SOURCE_FILES})
target_include_directories(raknet PUBLIC include)
target_link_libraries(raknet PRIVATE ${RAKNET_LIBRARY_LIBS})

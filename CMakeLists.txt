cmake_minimum_required(VERSION 3.21)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_SOURCE_FILES
    test/test_debouncer.cpp
)

set(TEST_INCLUDE_DIRS
    PUBLIC src
)

set(TEST_ADDITIONAL_LINK_LIBRARIES

)

include(submodules/DevTools/cmake/cjkGoogleTest.cmake)
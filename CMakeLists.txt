cmake_minimum_required(VERSION 3.21)
project(tinyLogicModules_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_SOURCE_FILES
    test/test_clockbasedTimer.cpp
    test/test_debouncer.cpp
    test/test_edgeDetector.cpp
    test/test_lerp.cpp
    test/test_sequenzer.cpp
)

set(TEST_INCLUDE_DIRS
    PUBLIC src
)

set(TEST_ADDITIONAL_LINK_LIBRARIES

)

include(submodules/DevTools/cmake/cjkGoogleTest.cmake)
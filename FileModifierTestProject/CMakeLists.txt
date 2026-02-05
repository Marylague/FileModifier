cmake_minimum_required(VERSION 3.21)

project(FileModifierTestProject VERSION 0.1 LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test)

qt_standard_project_setup()

qt_add_executable(FileProcessorTest
    tst_fileprocessortest.cpp
    tst_fileprocessortest.h
    ../fileprocessor.cpp
    ../fileprocessor.h
    tst_fileprocessortest.h
)
add_test(NAME FileProcessorTest COMMAND FileProcessorTest)


set_target_properties(FileProcessorTest PROPERTIES
    MACOSX_BUNDLE FALSE
    WIN32_EXECUTABLE FALSE
)

target_link_libraries(FileProcessorTest
    PRIVATE Qt6::Test
)

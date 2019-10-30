cmake_minimum_required(VERSION 3.10)
project(epi LANGUAGES CXX)

add_executable(epi_problem PUT THE SOURCE HERE!!!!)

target_include_directories(epi_problem
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Catch2/
)

target_compile_features(epi_problem
    PUBLIC cxx_std_17
)

target_compile_options(epi_problem
    PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-unused-variable
)
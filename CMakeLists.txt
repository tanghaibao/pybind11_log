cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0057 NEW)

project(PyBind11Log)

include_directories(include)

find_package(Python3 COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

pybind11_add_module(pybind11_log_test tests/pybind11_log_test.cpp)
target_link_libraries(pybind11_log_test PRIVATE spdlog::spdlog_header_only)
target_link_libraries(pybind11_log_test PRIVATE fmt::fmt-header-only)

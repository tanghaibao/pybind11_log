#include "pybind11_log.h"

#include <pybind11/pybind11.h>
#include <spdlog/spdlog.h>

int add(int i, int j) {
  spdlog::info("add({0}, {1})", i, j);
  return i + j;
}

int divide(int i, int j) {
  if (j == 0) {
    spdlog::error("Division by zero!");
    throw std::invalid_argument("Division by zero!");
  } else {
    spdlog::info("divide({0}, {1})", i, j);
  }
  return i / j;
}

PYBIND11_MODULE(pybind11_log_test, m) {
  pybind11_log::init();
  m.doc() = "pybind11_log example plugin";
  m.def("add", &add, "A function which adds two numbers with logging");
  m.def("divide", &divide, "A function which divides two numbers with logging");
}

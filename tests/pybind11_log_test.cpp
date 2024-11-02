#include "pybind11_log.h"

#include <pybind11/pybind11.h>
#include <spdlog/spdlog.h>

#include <thread>

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

void sleep_and_log() {
  spdlog::info("thread: will sleep for 1s");
  sleep(1);
  spdlog::info("thread: sleep completed");
}

void threaded_log() {
  py::gil_scoped_release release;  // Release the GIL when working with threads
  spdlog::info("threaded_log() starts");
  std::thread t1(sleep_and_log);
  t1.join();
  spdlog::info("threaded_log() ends");
}

void init(const std::string& logger_name) {
  pybind11_log::init_mt(logger_name);
}

PYBIND11_MODULE(pybind11_log_test, m) {
  m.doc() = "pybind11_log example plugin";
  m.def("init", &init, "Initialize the logger");
  m.def("add", &add, "A function which adds two numbers with logging");
  m.def("divide", &divide, "A function which divides two numbers with logging");
  m.def("threaded_log", &threaded_log,
        "A function which sleeps and log in a thread");
}

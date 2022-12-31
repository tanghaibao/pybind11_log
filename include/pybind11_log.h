#pragma once

#include <pybind11/pybind11.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/details/synchronous_factory.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>

#include <mutex>

namespace py = pybind11;

namespace pybind11_log {

int map_level(spdlog::level::level_enum level) {
  switch (level) {
    case spdlog::level::trace:
      return 5;
    case spdlog::level::debug:
      return 10;
    case spdlog::level::info:
      return 20;
    case spdlog::level::warn:
      return 30;
    case spdlog::level::err:
      return 40;
    case spdlog::level::critical:
      return 50;
    case spdlog::level::off:
    default:
      return 0;
  }
}

template <typename Mutex>
class pybind11_sink : public spdlog::sinks::base_sink<Mutex> {
 public:
  void sink_it_(const spdlog::details::log_msg& msg) override {
    std::string target = "pybind11_log";
    auto py_logging = py::module::import("logging");
    auto py_logger = py_logging.attr("getLogger")(target);
    std::string filename = msg.source.filename ? msg.source.filename : "";
    std::string msg_payload =
        std::string(msg.payload.begin(), msg.payload.end());
    auto record = py_logger.attr("makeRecord")(
        target, map_level(msg.level), filename, msg.source.line, msg_payload,
        py::none(), py::none());
    py_logger.attr("handle")(record);
  }

  void flush_() override {}
};

using pybind11_sink_mt = pybind11_sink<std::mutex>;
using pybind11_sink_st = pybind11_sink<spdlog::details::null_mutex>;

template <typename Factory = spdlog::synchronous_factory>
SPDLOG_INLINE std::shared_ptr<spdlog::logger> pybind11_mt(
    const std::string& logger_name) {
  return Factory::template create<pybind11_sink_mt>(logger_name);
}

template <typename Factory = spdlog::synchronous_factory>
SPDLOG_INLINE std::shared_ptr<spdlog::logger> pybind11_st(
    const std::string& logger_name) {
  return Factory::template create<pybind11_sink_st>(logger_name);
}

class Logger {
 public:
 private:
};

void init() {
  auto logger = pybind11_st("pybind11_log");
  spdlog::set_default_logger(logger);
}
}  // namespace pybind11_log
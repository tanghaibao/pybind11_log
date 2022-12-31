#pragma once

#include <spdlog/details/null_mutex.h>
#include <spdlog/details/synchronous_factory.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <mutex>

namespace pybind11_log {

template <typename Mutex>
class pybind11_sink : public spdlog::sinks::base_sink<Mutex> {
 public:
  void sink_it_(const spdlog::details::log_msg& msg) override {
    std::cout << msg.payload.data() << std::endl;
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

void init() {
  std::cout << "pybind11_log::init()" << std::endl;
  auto logger = pybind11_st("pybind11_log");
  spdlog::set_default_logger(logger);
}
}  // namespace pybind11_log
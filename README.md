# pybind11_log

A bridge from C++ to Python logging. Inspired by
[pyo3_log](https://docs.rs/pyo3-log/latest/pyo3_log/).

This works by routing the logging calls, e.g. `spdlog::info`, to the Python
`logging` module. This is done by setting the `spdlog::logger`'s `sink` to a
custom router sink. The router sink then calls the Python `logging` module.

## Usage

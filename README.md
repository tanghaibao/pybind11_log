# pybind11_log

A bridge from C++ to Python logging. Inspired by
[pyo3_log](https://docs.rs/pyo3-log/latest/pyo3_log/).

This works by routing the logging calls, e.g. `spdlog::info`, to the Python
`logging` module. This is done by setting the `spdlog::logger`'s `sink` to a
custom router sink. The router sink then calls the Python `logging` module.

## Usage

The library is header-only, so you can just include the header file
`include/pybind11_log.h` in your project.

```cpp
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
```

You can then test that the logging works by running the following Python code:

```python
import logging
import os
import sys

sys.path.append(os.getcwd())

from rich.logging import RichHandler

logging.basicConfig(
    level="NOTSET", format="%(message)s", datefmt="[%X]", handlers=[RichHandler()]
)

import pybind11_log_test

if __name__ == "__main__":
    pybind11_log_test.add(3, 4)
    pybind11_log_test.divide(3, 0)
```

As shown in the terminal output below, the logging calls are routed to Python
`logging` from the C++ code.

![log_test](images/log_test.png)
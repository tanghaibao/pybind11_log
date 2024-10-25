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
    #pybind11_log_test.divide(3, 0)
    pybind11_log_test.threaded_log()

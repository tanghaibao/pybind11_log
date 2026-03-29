import logging
import os
import sys

import pytest

# Add build directory to path so the compiled extension can be imported
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "build"))

import pybind11_log_test


@pytest.fixture(autouse=True, scope="session")
def init_logger():
    pybind11_log_test.init("test_logger")


def test_add(caplog):
    with caplog.at_level(logging.DEBUG, logger="test_logger"):
        result = pybind11_log_test.add(3, 4)
    assert result == 7
    assert "add(3, 4)" in caplog.text


def test_add_negative_numbers(caplog):
    with caplog.at_level(logging.DEBUG, logger="test_logger"):
        result = pybind11_log_test.add(-1, -2)
    assert result == -3


def test_divide(caplog):
    with caplog.at_level(logging.DEBUG, logger="test_logger"):
        result = pybind11_log_test.divide(10, 2)
    assert result == 5
    assert "divide(10, 2)" in caplog.text


def test_divide_by_zero(caplog):
    with caplog.at_level(logging.DEBUG, logger="test_logger"):
        with pytest.raises(Exception):
            pybind11_log_test.divide(3, 0)
    assert "Division by zero" in caplog.text


def test_threaded_log(caplog):
    with caplog.at_level(logging.DEBUG, logger="test_logger"):
        pybind11_log_test.threaded_log()
    assert "threaded_log() starts" in caplog.text
    assert "threaded_log() ends" in caplog.text
    assert "thread: will sleep for 1s" in caplog.text
    assert "thread: sleep completed" in caplog.text

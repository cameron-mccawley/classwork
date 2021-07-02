from word_count import *
import pytest

def test_normal_input():
    assert count_words("This is me making a unit test oh wow so neat") == 11

def test_random_chars():
    assert count_words("12 3 . ____ a b         cde") == 7

def test_empty_string():
    assert count_words("") == 0
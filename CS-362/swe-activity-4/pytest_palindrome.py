from palindrome import *
import pytest

def test_normal_input():
    assert palindrome("hannah") == True

def test_random_caps():
    assert palindrome("HanNah") == True

def test_not_palindrome():
    assert palindrome("not_a_palindrome") == False

def test_numbers_and_letters():
    assert palindrome("123 abc cba 321") == True
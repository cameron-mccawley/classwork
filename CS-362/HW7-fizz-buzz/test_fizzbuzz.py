from fizzbuzz import *
import unittest

class TestFizzBuzz(unittest.TestCase):
    def test_numbers(self):
        for i in [1, 2, 34, 98]:
            self.assertEqual(fizzbuzz(i), i)
        
    def test_fizz(self):
        for i in [3, 6, 9, 12]:
            self.assertEqual(fizzbuzz(i), "Fizz")

    def test_buzz(self):
        for i in [5, 10, 20, 25]:
            self.assertEqual(fizzbuzz(i), "Buzz")
        
    def test_fizzbuzz(self):
        for i in [15, 30, 45, 60]:
            self.assertEqual(fizzbuzz(i), "FizzBuzz")

if __name__ == '__main__':
    unittest.main()
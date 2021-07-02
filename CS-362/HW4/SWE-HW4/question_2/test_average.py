from average import *
import unittest

class TestMethods(unittest.TestCase):
    def test_get_average(self):
        #Test that it just works normally with valid inputs
        self.assertEqual(get_average([1, 2, 4, 56, 4, 6, 34, 40]), 18.375)

        #Test that dividing by 0 raises a divide by 0 error
        self.assertRaises(ZeroDivisionError, get_average, [])

        #Test negative numbers work
        self.assertEqual(get_average([1, -2, 4, -56, 4, 6, -34, 40]), -4.625)

        #Test that you can't find the average of a banana
        self.assertRaises(TypeError, get_average, ["banana", "apple", 54])

        #Test for a failure
        self.assertEqual(get_average([1]), 2)


if __name__ == '__main__':
    unittest.main()
from cube import *
import unittest

class TestMethods(unittest.TestCase):
    def test_calculate_volume(self):
        #Test that integers work
        self.assertEqual(calculate_volume(1, 2, 3), 6)

        #Test that floats are calculated correctly
        self.assertEqual(calculate_volume(4.5, 3.3, 8.7), 129.195)

        #Test that negative numbers dont give negative answer
        self.assertGreaterEqual(calculate_volume(-5, 4, 5.5), 0)

        #Test for very large numbers
        self.assertEqual(calculate_volume(123456789, 99999999999999999999999999, 99), 1.2222222111e+36)

        #Test that strings raise an exception
        self.assertRaises(ValueError, calculate_volume("banana", 3, 5))
        
if __name__ == '__main__':
    unittest.main()
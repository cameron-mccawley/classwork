from leapyear import *
import unittest

class test_leapyear(unittest.TestCase):
    def test_divisible_by_4(self):
        for i in [2001, 2002, 1943, 1827]:
            self.assertFalse(leap_year(i))
    
    def test_divisible_by_100_and_4(self):
        for i in [1700, 1800, 1900]:
            self.assertFalse(leap_year(i))
        
    def test_divisible_by_400(self):
        for i in [1200, 1600, 2000, 2400]:
            self.assertTrue(leap_year(i))

if __name__ == '__main__':
    unittest.main()
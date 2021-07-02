from leap_year import *
import unittest

class TestMethods(unittest.TestCase):
    def test_is_leap_year(self):
        self.assertTrue(leap_year(4))
        self.assertTrue(leap_year(400))
        self.assertTrue(leap_year(416))
        self.assertTrue(leap_year(16000))
    
    def test_is_not_leap_year(self):
        self.assertFalse(leap_year(1))
        self.assertFalse(leap_year(9))
        self.assertFalse(leap_year(500))
        self.assertFalse(leap_year(4001))

if __name__ == '__main__':
    unittest.main()
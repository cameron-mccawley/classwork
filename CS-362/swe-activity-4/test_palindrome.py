from palindrome import *
import unittest

class TestMethods(unittest.TestCase):
    def test_palindrome(self):
        self.assertTrue(palindrome("hannah"))
        self.assertTrue(palindrome("HanNah"))
        self.assertFalse(palindrome("not_a_palindrome"))
        self.assertTrue(palindrome("123 abc cba 321"))
        


if __name__ == '__main__':
    unittest.main()
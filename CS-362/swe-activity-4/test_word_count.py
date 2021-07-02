from word_count import *
import unittest

class TestMethods(unittest.TestCase):
    def test_count_words(self):
        self.assertEqual(count_words("This is me making a unit test oh wow so neat"), 11)
        self.assertEqual(count_words("12 3 . ____ a b         cde"), 7)
        self.assertEqual(count_words(""), 0)


if __name__ == '__main__':
    unittest.main()
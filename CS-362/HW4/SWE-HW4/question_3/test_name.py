from name import *
import unittest

class TestMethods(unittest.TestCase):
    def test_generate_name(self):
        #Test that it does what it supposed to do with valid input
        self.assertEqual(generate_name("Cameron", "McCawley"), "Cameron McCawley")

        #Test that it works with string numbers
        self.assertEqual(generate_name("123", "43"), "123 43",)

        #Test that it doesnt work for raw numbers
        self.assertRaises(TypeError, generate_name, 123, 43)

        #Test to see that it adds the space (This should fail)
        self.assertEqual(generate_name("Cameron", "McCawley"), "CameronMcCawley")


if __name__ == '__main__':
    unittest.main()
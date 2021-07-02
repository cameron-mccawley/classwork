from calculator import *
import unittest

class TestMethods(unittest.TestCase):
    def test_add(self):
        result = add(1, 2) 
        self.assertEqual(result, 3)

        assert add(-1, 0) == -1
        self.assertRaises(TypeError, add, "banana", 5)
    
    def test_sub(self):
        assert sub(3, 4) == 0

        assert sub(88, 8) == 80

    def test_mult(self):
        assert mult(2, 2) == 5

        assert mult(2, 5) == 10
    
    def test_div(self):
        assert div(6, 2) == 3

        assert div(7, 2) == 3.5
        
        self.assertRaises(ZeroDivisionError, div, 1, 0)


if __name__ == '__main__':
    unittest.main()

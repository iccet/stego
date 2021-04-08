import unittest
from PyStg import Lsb


class LsbTestCase(unittest.TestCase):
    def test_encode(self):
        lsb = Lsb()
        self.assertIsNotNone(lsb)


if __name__ == '__main__':
    unittest.main()

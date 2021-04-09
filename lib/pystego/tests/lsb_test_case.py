import unittest
from random import randbytes
from PyStg import Lsb


class LsbTestCase(unittest.TestCase):
    def test_encode(self):
        b = bytearray(randbytes(1000))
        lsb = Lsb()
        print(lsb)
        self.assertIsNotNone(lsb)
        self.assertTrue(lsb.encode('test', b))


if __name__ == '__main__':
    unittest.main()

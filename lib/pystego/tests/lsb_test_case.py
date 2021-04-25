import unittest
from random import randbytes
from PyStg import Lsb

required_methods = ('encode', 'decode')


class LsbTestCase(unittest.TestCase):

    def setUp(self):
        self.lsb = Lsb()
        self.container = bytearray(randbytes(1000))
        self.data = 'test'

    def test_doc(self):
        self.assertIn('__doc__', dir(Lsb))
        self.assertIsNotNone(Lsb.__doc__)

    def test_init(self):
        self.assertIsNotNone(self.lsb)

    def test_attrs(self):
        for m in required_methods:
            self.assertIn(m, dir(Lsb))

    def test_encode_args(self):
        self.assertTrue(self.lsb.encode(self.data, self.container))

    def test_encode_kwargs(self):
        self.assertTrue(self.lsb.encode(container=self.container, data=self.data))

    def test_encode_exception(self):
        with self.assertRaises(TypeError):
            self.lsb.encode(self.data, int())

        with self.assertRaises(TypeError):
            self.lsb.encode(self.data, self.data)

    def test_decode_args(self):
        self.lsb.encode(self.data, self.container)
        self.assertEqual(self.lsb.decode(self.container), self.data)

    def test_decode_kwargs(self):
        self.lsb.encode(self.data, self.container)
        self.assertEqual(self.lsb.decode(container=self.container), self.data)


if __name__ == '__main__':
    unittest.main()

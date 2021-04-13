import unittest
from random import randbytes
from PyStg import Kutter

required_methods = ('encode', 'decode')


class KutterTestCase(unittest.TestCase):

    def setUp(self):
        self.kutter = Kutter()
        self.container = bytearray(randbytes(1000))
        self.data = 'test'

    def test_doc(self):
        self.assertIn('__doc__', dir(Kutter))
        self.assertIsNotNone(Kutter.__doc__)

    def test_init(self):
        self.assertIsNotNone(self.kutter)

    def test_attrs(self):
        for m in required_methods:
            self.assertIn(m, dir(Kutter))

    def test_encode_args(self):
        self.assertTrue(self.kutter.encode(self.data, self.container))

    def test_encode_kwargs(self):
        self.assertTrue(self.kutter.encode(container=self.container, data=self.data))

    def test_encode_exception(self):
        with self.assertRaises(TypeError):
            self.kutter.encode(self.data, int())

        with self.assertRaises(TypeError):
            self.kutter.encode(self.data, self.data)

    def test_decode_args(self):
        self.kutter.encode(self.data, self.container)
        self.assertEqual(self.kutter.decode(self.container), self.data)

    def test_decode_kwargs(self):
        self.kutter.encode(self.data, self.container)
        self.assertEqual(self.kutter.decode(container=self.container), self.data)


if __name__ == '__main__':
    unittest.main()

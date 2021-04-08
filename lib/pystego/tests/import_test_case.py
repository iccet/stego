import unittest
import PyStg


class ImportTestCase(unittest.TestCase):
    def test_module_dict(self):
        self.assertIsNotNone(dir(PyStg))


if __name__ == '__main__':
    unittest.main()

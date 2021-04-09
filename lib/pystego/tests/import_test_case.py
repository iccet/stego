import unittest
import PyStg


class ImportTestCase(unittest.TestCase):
    def test_doc_exist(self):
        self.assertIsNotNone(PyStg.__doc__)

    def test_module_dict(self):
        self.assertIsNotNone(dir(PyStg))

    def test_all_modules_exist(self):
        d = dir(PyStg)
        self.assertIn('Lsb', d)
        self.assertIn('Kutter', d)


if __name__ == '__main__':
    unittest.main()

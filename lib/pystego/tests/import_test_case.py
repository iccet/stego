import unittest
import PyStg

required_members = ('Lsb', 'Kutter')


class ImportTestCase(unittest.TestCase):

    def test_version(self):
        self.assertIn('__version__', dir(PyStg))
        self.assertIsNotNone(PyStg.__version__)

    @unittest.skipIf(tuple(map(int, PyStg.__version__.split('.'))) < (1, 0), "Allowed to empty doc string")
    def test_doc_exist(self):
        self.assertIsNotNone(PyStg.__doc__)

    def test_module_dict(self):
        self.assertIsNotNone(dir(PyStg))

    def test_all_modules_exist(self):
        for m in required_members:
            self.assertIn(m, dir(PyStg))


if __name__ == '__main__':
    unittest.main()

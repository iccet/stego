#include "pystg.hpp"

PyModuleDef PyStg =
{
    PyModuleDef_HEAD_INIT,
    .m_name = "PyStg",
    .m_doc = "PYSTG",
    .m_size = -1,
};

int PyModule_AddType(PyObject *module, const char *name, PyTypeObject *type)
{
    if (PyType_Ready(type) < 0) return -1;

    Py_INCREF(type);
    if (PyModule_AddObject(module, name, (PyObject *)type) < 0)
    {
        Py_DECREF(type);
        Py_DECREF(module);
        return -1;
    }
    return 0;
}

PyMODINIT_FUNC PyInit_PyStg()
{
    PyObject *module = PyModule_Create(&PyStg);
    if (module == NULL) return NULL;

    PyModule_AddType(module, "Lsb", &PyType_Lsb);

    return module;
}

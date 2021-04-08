#include "pystg.hpp"


PyMethodDef PyLsbMethods[] =
{
    {"encode", (PyCFunction) encode, METH_VARARGS, "encode matrix"},
    {NULL, NULL, 0, NULL}
};

PyTypeObject PyType_Lsb =
{
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "PyStg.lsb",
    .tp_basicsize = sizeof(PyLsb),
    .tp_dealloc = (destructor) __del__,
    .tp_repr = (reprfunc) __repr__,
    .tp_str = (reprfunc) __repr__,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Steganography using LSB algorithm",
    .tp_methods = (PyMethodDef *) PyLsbMethods,
    .tp_init = (initproc) __init__,
    .tp_alloc = (allocfunc) PyType_GenericAlloc,
    .tp_new = (newfunc) PyType_GenericNew,
};

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

    PyModule_AddType(module, "lsb", &PyType_Lsb);

    return module;
}

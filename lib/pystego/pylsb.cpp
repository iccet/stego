#include "pylsb.hpp"

int __init__(PyLsb * self)
{
    return 0;
}

void __del__(PyLsb * self)
{
    Py_TYPE(self)->tp_free(self);
}

PyObject * __repr__(PyLsb * self)
{
    std::string str = self->_impl->metaObject()->className();
    char * cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());

    PyObject * res_str = Py_BuildValue("s", cstr);
    delete [] cstr;
    return res_str;
}

void encode(PyLsb * self)
{
//        (self->_impl)->encode();
}

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

#include "pylsb.hpp"

int __init__(PyLsb * self, PyObject * args)
{
    int m, n;
    PyObject * list;
    double ** array;

    if (!PyArg_ParseTuple(args, "O", &list))
    {
        return -1;
    }

    m = PyList_Size(list);
    array = new double * [m];
    PyObject * iter = PyObject_GetIter(list);
    if (!iter) {
        return -1;
    }

    for(int i = 0; i < m; i++)
    {
        PyObject * row = PyIter_Next(iter);
        n = PyList_Size(row);
        array[i] = new double[n];
        if (!row) break;
        if (!PyList_Check(row)) return -1;

        PyObject * col = PyObject_GetIter(row);
        for(int j = 0; j < n; j++)
        {
            PyObject *el = PyIter_Next(col);
            if (!el) break;
            array[i][j] = PyFloat_AsDouble(el);
        }
    }
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

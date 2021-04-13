#ifndef PYSTG_HPP
#define PYSTG_HPP

#include "pylsb.hpp"

int PyModule_AddType(PyObject * module, const char * name, PyTypeObject * type);

PyMODINIT_FUNC PyInit_PyStg();

#endif // PYSTG_HPP

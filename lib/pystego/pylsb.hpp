#ifndef PYLSB_HPP
#define PYLSB_HPP

#include <boost/python.hpp>

#include "globconf.hpp"
#include "lsb.hpp"

extern PyTypeObject PyType_Lsb;

typedef struct
{
    PyObject_HEAD;
    Stg::Lsb *_impl;
} PyLsb;

int __init__(PyLsb *self);
void __del__(PyLsb *self);

PyObject *__new__(PyTypeObject *type, PyObject *args, PyObject *kwargs);
PyObject *__repr__(PyLsb *self);

void encode(PyLsb *self);

#endif // PYLSB_HPP

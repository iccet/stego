#ifndef PYLSB_HPP
#define PYLSB_HPP

#include "globconf.hpp"
#include "lsb.hpp"

typedef struct
{
    PyObject_HEAD;
    Stg::Lsb *_impl;
} PyLsb;

int __init__(PyLsb *self, PyObject *args);
void __del__(PyLsb *self);

PyObject *__new__(PyTypeObject *type, PyObject *args, PyObject *kwargs);
PyObject *__repr__(PyLsb *self);

void encode(PyLsb *self);

#endif // PYLSB_HPP

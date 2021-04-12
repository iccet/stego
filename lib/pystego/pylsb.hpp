#ifndef PYLSB_HPP
#define PYLSB_HPP

#include <iostream>
#include <QString>

#include <boost/python.hpp>
#include <boost/log/trivial.hpp>

#include "globconf.hpp"
#include "lsb.hpp"

template<typename T>
struct True : std::unary_function<T, bool>
{
    bool operator () (T value){ return value; }
};

struct PyLsb
{
    PyLsb() = default;


    bool encode(std::string data, PyObject *container);

private:
    Stg::Lsb _impl;
};

#endif // PYLSB_HPP

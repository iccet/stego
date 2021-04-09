#ifndef PYLSB_HPP
#define PYLSB_HPP

#include <iostream>

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
    PyLsb(std::reference_wrapper<const struct PyLsb>::type &type);


    bool encode();

private:
    Stg::Lsb _impl;
};

#endif // PYLSB_HPP

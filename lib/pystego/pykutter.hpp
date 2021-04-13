#ifndef PYKUTTER_HPP
#define PYKUTTER_HPP

#include "globconf.hpp"
#include "kutter.hpp"

extern void checkContainerType(PyObject *container);

struct PyKutter
{
    PyKutter() = default;

    bool encode(const std::string& data, PyObject *container);
    std::string decode(PyObject *container);

private:
    Stg::Kutter _impl;
};

#endif //PYKUTTER_HPP

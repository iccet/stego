#ifndef PYKUTTER_HPP
#define PYKUTTER_HPP

#include <boost/python.hpp>

#include "globconf.hpp"
#include "kutter.hpp"

using namespace boost::python;

extern void checkContainerType(PyObject *container);

struct PyKutter
{
    using dimension = std::tuple<int, int>;

    PyKutter() = default;

    bool encode(const std::string& data, PyObject *container);
    std::string decode(PyObject *container, const object& args = object());

private:
    Stg::Kutter _impl;
};

#endif //PYKUTTER_HPP

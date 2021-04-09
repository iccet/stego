#ifndef PYKUTTER_HPP
#define PYKUTTER_HPP

#include "globconf.hpp"
#include "kutter.hpp"

struct PyKutter
{
    PyKutter() = default;
    PyKutter(std::reference_wrapper<const struct PyLsb>::type &type);


    bool encode();

private:
    Stg::Kutter _impl;
};

#endif //PYKUTTER_HPP

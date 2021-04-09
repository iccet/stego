#include "pystg.hpp"

BOOST_PYTHON_MODULE(PyStg)
{
    class_<PyLsb, boost::noncopyable>("Lsb", "Steganography using LSB algorithm")
        .def("encode", &PyLsb::encode)
        ;

    class_<PyKutter, boost::noncopyable>("Kutter", "Kutter steganographical method")
        .def("encode", &PyKutter::encode)
        ;
}

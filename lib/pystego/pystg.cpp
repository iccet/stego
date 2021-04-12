#include "pystg.hpp"

BOOST_PYTHON_MODULE(PyStg)
{
    scope().attr("__version__") = std::string(PROJECT_VERSION);
    scope().attr("__doc__") = std::string(PROJECT_NAME);

    std::cout << "init finished\n";
    class_<PyLsb, boost::noncopyable>("Lsb", "Steganography using LSB algorithm")
        .def("encode", &PyLsb::encode)
        ;

    class_<PyKutter, boost::noncopyable>("Kutter", "Kutter steganographical method")
        .def("encode", &PyKutter::encode)
        ;
}

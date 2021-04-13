#include "pystg.hpp"

void checkContainerType(PyObject *container)
{
    if(!PyByteArray_Check(container))
        throw std::invalid_argument(
            QString("Invalid container type: must be bytearray got %0")
                .arg(Py_TYPE(container)->tp_name).toStdString());
}

void translate(std::invalid_argument const& e)
{
    PyErr_SetString(PyExc_TypeError, e.what());
}

BOOST_PYTHON_MODULE(PyStg)
{
    register_exception_translator<std::invalid_argument>(&translate);

    scope().attr("__version__") = std::string(PROJECT_VERSION);
    scope().attr("__doc__") = std::string(PROJECT_NAME);

    class_<PyLsb, boost::noncopyable>("Lsb", "Steganography using LSB algorithm")
        .def("encode", &PyLsb::encode, (arg("data"), arg("container")))
        .def("decode", &PyLsb::decode, (arg("container")));

    class_<PyKutter, boost::noncopyable>("Kutter", "Kutter steganographical method")
        .def("encode", &PyKutter::encode, (arg("data"), arg("container")))
        .def("decode", &PyKutter::decode, (arg("container")));
}

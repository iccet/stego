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

struct tuple_to_python_tuple
{
    using type = PyKutter::dimension;
    static PyObject* convert(type const &s)
    {
        return boost::python::incref(make_tuple(std::get<0>(s), std::get<1>(s)).ptr());
    }
};

struct tuple_from_python_tuple
{
    using type = PyKutter::dimension;

    tuple_from_python_tuple()
    {
        converter::registry::push_back(
            &convertible,
            &construct,
            type_id<type>());
    }

    static void* convertible(PyObject* o)
    {
        return PyTuple_Check(o) && PyTuple_Size(o) >= 2 ? o : nullptr;
    }

    static void construct(
            PyObject* obj_ptr,
            converter::rvalue_from_python_stage1_data* data)
    {
        auto value = std::make_tuple(
                PyLong_AsLong(PyTuple_GetItem(obj_ptr, 0)),
                PyLong_AsLong(PyTuple_GetItem(obj_ptr, 1)));

        auto storage = reinterpret_cast<converter::rvalue_from_python_storage<type> *>(data)->storage.bytes;
        new (storage) type(value);
        data->convertible = storage;
    }
};

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(kutter_decode_overloads, PyKutter::decode, 1, 2);

BOOST_PYTHON_MODULE(PyStg)
{
    register_exception_translator<std::invalid_argument>(&translate);

    to_python_converter<PyKutter::dimension, tuple_to_python_tuple>();
    tuple_from_python_tuple();

    scope().attr("__version__") = std::string(PROJECT_VERSION);
    scope().attr("__doc__") = std::string(PROJECT_NAME);

    class_<PyLsb, boost::noncopyable>("Lsb", "Steganography using LSB algorithm")
        .def("encode", &PyLsb::encode, (arg("data"), arg("container")))
        .def("decode", &PyLsb::decode, (arg("container")));

    class_<PyKutter, boost::noncopyable>("Kutter", "Kutter steganographical method")
        .def("encode", &PyKutter::encode, (arg("data"), arg("container")))
        .def("decode", &PyKutter::decode, kutter_decode_overloads(args("container", "args")));
}

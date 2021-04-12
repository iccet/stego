#include "pylsb.hpp"

bool PyLsb::encode(const std::string& data, PyObject *container)
{
    checkContainerType(container);

    return _impl.Base::encode(
        QString::fromStdString(data),
        (uchar *)PyByteArray_AsString(container),
        PyByteArray_Size(container));
}

std::string PyLsb::decode(PyObject *container)
{
    checkContainerType(container);
    auto size = PyByteArray_Size(container);
    auto bytes = (uchar *)PyByteArray_AsString(container);

    return {_impl.Base::decode(bytes, size).data()};
}

void PyLsb::checkContainerType(PyObject *container)
{
    if(!PyByteArray_Check(container))
        throw std::invalid_argument(
            QString("Invalid container type: must bytearray got %0")
                .arg(Py_TYPE(container)->tp_name).toStdString());
}

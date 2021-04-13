#include "pykutter.hpp"

bool PyKutter::encode(const std::string& data, PyObject *container)
{
    checkContainerType(container);

    return _impl.Base::encode(
        QString::fromStdString(data),
        (uchar *)PyByteArray_AsString(container),
        PyByteArray_Size(container));
}

std::string PyKutter::decode(PyObject *container)
{
    checkContainerType(container);
    auto size = PyByteArray_Size(container);
    auto bytes = (uchar *)PyByteArray_AsString(container);

    return std::string(_impl.Base::decode(bytes, size).data(), size);
}

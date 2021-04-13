#include <iostream>
#include "pykutter.hpp"

bool PyKutter::encode(const std::string& data, PyObject *container)
{
    checkContainerType(container);

    return _impl.Base::encode(
        QString::fromStdString(data),
        (uchar *)PyByteArray_AsString(container),
        PyByteArray_Size(container));
}

std::string PyKutter::decode(PyObject *container, const object& args)
{
    checkContainerType(container);
    auto size = PyByteArray_Size(container);
    auto bytes = (uchar *)PyByteArray_AsString(container);

    if(args.is_none())
        return QString(_impl.Base::decode(bytes, size)).toUtf8().toStdString();

    else if(auto extracted = extract<dimension>(args); extracted.check())
    {
        auto [h, w] = (dimension)extracted;
        return QString(_impl.decode(bytes, size, h, w)).toUtf8().toStdString();
    }

    throw std::invalid_argument(
            QString("Invalid dimension arg: must be tuple<int, int> got %0")
                    .arg(Py_TYPE(args.ptr())->tp_name).toStdString());
}

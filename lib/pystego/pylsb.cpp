#include "pylsb.hpp"

bool PyLsb::encode(std::string data, PyObject *container)
{
    if(!PyByteArray_Check(container))
        throw std::invalid_argument(
                QString("Invalid container type: must bytearray got %0")
                .arg(Py_TYPE(container)->tp_name).toStdString());

    auto size = PyByteArray_Size(container);
    auto bytes = (uchar *)PyByteArray_AsString(container);

    if(!_impl.Base::encode(QString::fromStdString(data), bytes, size)) return false;

    for(auto i = 0; i < size; i++)
    {
        PySequence_SetItem(container, i, Py_BuildValue("b", bytes[i]));
    }
    return true;
}

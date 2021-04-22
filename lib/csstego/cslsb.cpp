#include "cslsb.hpp"

bool Encode(const char *data, uchar *container, int32_t size)
{
    return Lsb().Base::encode(data, container, size);
}

int32_t Decode(const uchar *container, int32_t size, const char *&data)
{
    auto decoded = QString(Lsb().Base::decode(container, size).data());
    qDebug() << "Decoding" << decoded;
    data = decoded.toLocal8Bit().data();
    return decoded.length();
}

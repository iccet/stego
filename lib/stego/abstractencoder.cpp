#include "abstractencoder.hpp"

namespace Stg
{
    bool AbstractEncoder::encode(QString data, uchar *container, int size)
    {
        QByteArray bytes = QByteArray::fromRawData((const char *)container, size);
        if(!encode(data, bytes)) return 0;

        int i = 0;
        foreach(auto byte, bytes)
        {
            container[i++] = byte;
        }

        return 1;
    }

    QByteArray AbstractEncoder::decode(const uchar *container, int size)
    {
        QByteArray bytes = QByteArray::fromRawData((const char*)container, size);
        return decode(bytes);
    }

    bool AbstractEncoder::encode(const char *data, uchar *container, int size)
    {
        return encode(QString(data), container, size);
    }

} // namespace PyStg

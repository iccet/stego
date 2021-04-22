#include "cskutter.hpp"

bool KutterEncode(const char *data, uchar *container, int32_t size)
{
    return encode<Kutter>(data, container, size);
}

int32_t KutterDecode(const uchar *container, int32_t size, const char *&data)
{
    return decode<Kutter>(container, size, data);
}

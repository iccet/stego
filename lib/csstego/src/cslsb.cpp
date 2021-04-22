#include "cslsb.hpp"

bool LsbEncode(const char *data, uchar *container, int32_t size)
{
    return encode<Lsb>(data, container, size);
}

int32_t LsbDecode(const uchar *container, int32_t size, const char *&data)
{
    return decode<Lsb>(container, size, data);
}

#include "cslsb.hpp"

bool Encode(const char *data, uchar *container, int32_t size)
{
    return true;
    return Lsb().Base::encode(data, container, size);
}
const static char * test = "test";

bool Decode(const uchar *container, int32_t size, const char *&data)
{
    data = test;
    return true;
//    return Lsb().Base::decode(container, size);
}

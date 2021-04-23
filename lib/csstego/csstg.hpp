#ifndef CSSTG_HPP
#define CSSTG_HPP

#include "csstg_export.h"

#define BASE_ENCODE_DECL(Class) bool CSSTG_EXPORT Class##Encode(const char *data, uchar *container, int32_t size);
#define BASE_DECODE_DECL(Class) int32_t CSSTG_EXPORT Class##Decode(const uchar *container, int32_t size, const char *&data);

#define BASE_ENCODE_IMPL(Class) bool Class##Encode(const char *data, uchar *container, int32_t size)\
{ return encode<Class>(data, container, size); }

#define BASE_DECODE_IMPL(Class) int32_t Class##Decode(const uchar *container, int32_t size, const char *&data)\
{ return decode<Class>(container, size, data);}

#define BASE_DECL(Class) \
BASE_DECODE_DECL(Class)  \
BASE_ENCODE_DECL(Class)

#define BASE_IMPL(Class) \
BASE_DECODE_IMPL(Class)  \
BASE_ENCODE_IMPL(Class)

#endif //CSSTG_HPP

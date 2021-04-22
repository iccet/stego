#ifndef CSKUTTER_HPP
#define CSKUTTER_HPP

#include <cstdint>
#include "csstg_export.h"
#include "kutter.hpp"
#include "stg.hpp"

using namespace Stg;

#ifdef __cplusplus
extern "C" {
#endif

bool CSSTG_EXPORT KutterEncode(const char *data, uchar *container, int32_t size);
int32_t CSSTG_EXPORT KutterDecode(const uchar *container, int32_t size, const char *&data);

#ifdef __cplusplus
}
#endif


#endif //LIBS_CSKUTTER_HPP

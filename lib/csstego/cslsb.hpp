#ifndef CSSTG_LIBRARY_H
#define CSSTG_LIBRARY_H

#include <cstdint>
#include <boost/log/trivial.hpp>

#include "csstg_export.h"
#include "lsb.hpp"

using namespace Stg;

#ifdef __cplusplus
extern "C" {
#endif

bool CSSTG_EXPORT Encode(const char *data, uchar *container, int32_t size);
bool CSSTG_EXPORT Decode(const uchar *container, int32_t size, const char *&data);

#ifdef __cplusplus
}
#endif

#endif //CSSTG_LIBRARY_H

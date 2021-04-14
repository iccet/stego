#ifndef CSSTG_LIBRARY_H
#define CSSTG_LIBRARY_H

#include <cstdint>

#include "csstg_export.h"
#include <boost/log/trivial.hpp>

#ifdef __cplusplus
extern "C" {
#endif

bool CSSTG_EXPORT Encode(const char *data, char *container, int64_t size);
const char *CSSTG_EXPORT Decode(char *container, int64_t size);

#ifdef __cplusplus
}
#endif

#endif //CSSTG_LIBRARY_H

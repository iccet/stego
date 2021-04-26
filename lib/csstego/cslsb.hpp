#ifndef CSSTG_LIBRARY_H
#define CSSTG_LIBRARY_H

#include <cstdint>
#include <boost/log/trivial.hpp>

#include "csstg_export.h"
#include "lsb.hpp"
#include "csstg.hpp"
#include "stg.hpp"

using namespace Stg;

#ifdef __cplusplus
extern "C" {
#endif

BASE_DECL(Lsb);

#ifdef __cplusplus
}
#endif

#endif //CSSTG_LIBRARY_H

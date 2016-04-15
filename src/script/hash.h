#ifndef PNL_HASH_H
#define PNL_HASH_H

#include "../util/types.h"

namespace Ice { namespace Script {

  // Bob Jenkins One at a Time hash.

  u32 hash( void* key, i32 length );

} }

#endif // PNL_HASH_H
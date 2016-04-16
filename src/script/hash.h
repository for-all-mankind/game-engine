#ifndef ICE_SCRIPT_HASH_H
#define ICE_SCRIPT_HASH_H

#include "../util/types.h"

#include <string>

namespace Ice { namespace Script {

  // Bob Jenkins One at a Time hash.

  u32 hash( void* key, i32 length );
  u32 hash( const std::string& string );

} }

#endif // ICE_SCRIPT_HASH_H
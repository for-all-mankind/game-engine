#include "Hash.hpp"

#include <cstdio>

namespace Ice { namespace Script {

  u32 hash( void* key, i32 length )
  {
    u8* p = static_cast<u8*>( key );
    u32 h = 0;

    for ( i32 i = 0; i < length; ++i )
    {
      h += p[ i ];
      h += ( h << 10 );
      h ^= ( h >> 6  );
    }

    h += ( h << 3  );
    h ^= ( h >> 11 );
    h += ( h << 15 );

    return h;
  }

  u32 hash( const std::string& string )
  {
    const u32 length = string.length();
          u32 result;

    char* buffer = new char[ length ];

    sprintf( buffer, "%s", string.data() );

    result = hash( buffer, length );

    delete buffer;
    return result;
  }

} }
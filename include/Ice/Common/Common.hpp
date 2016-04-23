#ifndef ICE_COMMON_HPP
#define ICE_COMMON_HPP

#include <Ice/Common/Types.hpp>

#include <stdexcept>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <functional>
#include <limits>
#include <memory>

namespace Impl
{
  template <typename Fn>
  struct Defer
  {
    Defer( Fn&& fn )
      : fn{ std::forward<Fn>( fn ) }
    {}

    ~Defer() { fn(); };

    Fn fn;
  };

  template <typename Fn>
  Defer<Fn> deferFn( Fn&& fn )
  {
    return Defer<Fn>( std::forward<Fn>( fn ) );
  }
}

#define DEFER_1( x, y ) x##y
#define DEFER_2( x, y ) DEFER_1( x, y )
#define DEFER_3( x    ) DEFER_2( x, __COUNTER__ )
#define defer( code ) auto DEFER_3( _defer_ ) = Impl::deferFn( [&](){code;} );

#endif // ICE_COMMON_HPP
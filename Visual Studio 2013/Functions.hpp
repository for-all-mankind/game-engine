#ifndef ICE_MATHS_FUNCTIONS_HPP
#define ICE_MATHS_FUNCTIONS_HPP

#include "Types.hpp"

namespace Ice
{
  #define VECTOR_FUNCTIONS( N, T )          \
    inline T operator*( f32 l, const T& r ) \
    {                                       \
      T result;                             \
                                            \
      for ( usize i = 0; i < N; ++i )       \
        result[i] = l * r[i];               \
                                            \
      return result;                        \
    }                                       \
                                            \
    inline f32 dot( const T& a, const T& b )\
    {                                       \
      f32 result = 0.0f;                    \
                                            \
      for ( usize i = 0; i < N; ++i )       \
        result += a[i] * b[i];              \
                                            \
      return result;                        \
    }                                       \
                                            \
    inline f32 length( const T& a )         \
    {                                       \
      return sqrtf( dot( a, a ) );          \
    }                                       \
                                            \
    inline f32 length_squared( const T& a ) \
    {                                       \
      return dot( a, a );                   \
    }                                       \
                                            \
    inline void normalise( T& a )           \
    {                                       \
      a /= length( a );                     \
    }                                       \
                                            \
    inline T normalised( const T& a )       \
    {                                       \
      return a / length( a );               \
    }
}

#endif // ICE_MAHTS_FUNCTIONS_HPP
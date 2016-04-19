#ifndef ICE_NON_COPY_H
#define ICE_NON_COPY_H

#include <Ice/Common/Types.hpp>

namespace Ice { namespace Common {

  class NonCopyable
  {
  protected:
    NonCopyable() {}

  private:
    NonCopyable( const NonCopyable&  copy ) = delete;
    NonCopyable(       NonCopyable&& move ) = delete;

    NonCopyable& operator=( const NonCopyable&  copy ) = delete;
    NonCopyable& operator=(       NonCopyable&& move ) = delete;
  };

} }

#endif // ICE_NON_COPY_H
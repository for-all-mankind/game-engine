#ifndef ICE_COMMON_FILE_H
#define ICE_COMMON_FILE_H

#include <Ice/Common/Types.hpp>

namespace Ice { namespace Common {

  void read_file  ( const std::string& filename, std::string* contents );
  bool file_exists( const std::string& filename );

} }

#endif // ICE_COMMON_FILE_H
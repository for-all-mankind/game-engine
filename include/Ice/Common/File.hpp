#ifndef INDIE_CIV_ENGINE_FILE_H
#define INDIE_CIV_ENGINE_FILE_H

#include <Ice/Common/Types.hpp>

namespace Ice { namespace Common {

  void read_file  ( const std::string& filename, std::string* contents );
  bool file_exists( const std::string& filename );

} }

#endif // INDIE_CIV_ENGINE_FILE_H
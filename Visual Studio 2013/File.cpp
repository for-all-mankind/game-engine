#include "File.hpp"
#include "Common.hpp"

namespace Ice { namespace Common {

  void read_file( const std::string& filename, std::string* contents )
  {
    std::ifstream     file( filename );
    std::string       line;
    std::stringstream stream;

    if ( !file.good() )
      std::cout << "Unable to open file: '" << filename << "'" << std::endl;

    while ( getline( file, line ) )
      stream << line << "\n";

    *contents = stream.str();
  }

} }
#ifndef ICE_SCRIPT_TYPE_TABLE
#define ICE_SCRIPT_TYPE_TABLE

#include "../util/types.h"

#include <string>
#include <vector>

namespace Ice { namespace Script {

  class TypeTable
  {
  public:
    bool Check( const std::string& type_name );
    void Add  ( const std::string& type_name );
    void Alias( const std::string& alias, const std::string& type_name );

  private:
    bool Check( u32 hash_name );

  private:
    // The actual types that exist in
    // the program.
    std::vector<u32> _table;

    // A collection of alias types.
    std::unordered_map<u32, u32> _alias;
  };

} }

#endif // ICE_SCRIPT_TYPE_TABLE
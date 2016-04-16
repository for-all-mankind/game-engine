#include "type_table.h"
#include "hash.h"

namespace Ice { namespace Script {

  bool TypeTable::Check( const std::string& type_name )
  {
    u32 h = hash( type_name );

    bool found_type = Check( h );

    if ( !found_type )
    {
      auto found = _alias.find( h );

      if ( found != _alias.end() )
        return Check( found->second );
    }

    return found_type;
  }

  bool Check( u32 hash_name )
  {
    for ( u32 t : _table )
    {
      if ( h == t )
        return true;
    }

    return false;
  }

  void TypeTable::Add( const std::string& type_name )
  {
    _table.emplace_back( hash( type_name ) );
  }

  void Alias( const std::string& alias, const std::string& type_name )
  {
    hash_alias = hash( alias     );
    hash_type  = hash( type_name );

    _alias.emplace( hash_alias, hash_type );
  }

} }
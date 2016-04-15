#include "symbol_table.h"

namespace Ice { namespace Script {

  SymbolTable::SymbolTable( SymbolTable* parent )
    : _parent_scope( parent )
  {}

  bool SymbolTable::Check ( const std::string& symbol_name )
  {
    auto found = _symbols.find( symbol_name );

    if ( found == _symbols.end() )
      return false;

    return true;
  }

  void SymbolTable::Insert( const std::string& symbol_name, const Symbol& symbol )
  {
    // TODO: check if it already exists?
    _symbols.emplace( symbol_name, symbol );
  }

  Symbol* SymbolTable::LookUp( const std::string& symbol_name )
  {
    auto found = _symbols.find( symbol_name );

    // We didn't find the symbol here, lets check
    // the parent scope.
    if ( found == _symbols.end() )
    {
      // Oh. We can't check the parent scope... there
      // isn't one.
      if ( _parent_scope == nullptr )
        return nullptr;

      return _parent_scope->LookUp( symbol_name );
    }
    else
      return &(found->second);
  }

} }
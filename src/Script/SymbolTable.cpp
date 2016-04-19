#include <Ice/Script/SymbolTable.hpp>

namespace Ice { namespace Script {

  SymbolTable::SymbolTable( SymbolTable* parent )
    : _parent_scope( parent )
  {}

  SymbolTable::~SymbolTable()
  {
    for ( auto pair : _symbols )
    {
      Symbol* s = &pair.second;

      if ( s->info != nullptr )
        switch ( s->type )
        {
          case SymbolType::VARIABLE:
            delete static_cast<VariableInfo*>( s->info );
          case SymbolType::FUNCTION:
            delete static_cast<FunctionInfo*>( s->info );
          case SymbolType::CLASS:
            delete static_cast<ClassInfo*>( s->info );
          case SymbolType::OBJECT:
            delete static_cast<ObjectInfo*>( s->info );
          case SymbolType::STRUCT:
            delete static_cast<StructInfo*>( s->info );
          case SymbolType::ENUM:
            delete static_cast<EnumInfo*>( s->info );
          case SymbolType::INTERFACE:
            delete static_cast<ierfaceInfo*>( s->info );
          case SymbolType::ARRAY:
            delete static_cast<ArrayInfo*>( s->info );
          case SymbolType::TYPE:
            delete static_cast<TypeInfo*>( s->info );
        }
    }
  }

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
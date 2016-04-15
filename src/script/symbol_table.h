#ifndef PNL_SYMBOL_TABLE_H
#define PNL_SYMBOL_TABLE_H

#include "../util/types.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace Ice { namespace Script {

  struct Symbol;
  class  SymbolTable;

  /////////////////////////////////

  enum class SymbolType
  {
    VARIABLE,
    FUNCTION,
    CLASS,
    STRUCT,
    ENUM,
    INTERFACE,
    ARRAY
  };

  /////////////////////////////////

  enum class DataType
  {
    VOID,
    I8,
    I16,
    I32,
    I64,
    U8,
    U16,
    U32,
    U64,
    F32,
    F64,
    BOOLEAN,
    CHAR,
    STRING
  };

  /////////////////////////////////

  struct VariableInfo
  {
    DataType type;
  };

  /////////////////////////////////

  struct FunctionInfo
  {
    DataType return_type;
    u32      number_args;

    VariableInfo* args;
  };

  /////////////////////////////////

  struct ClassInfo
  {
    bool has_ctor;
    bool has_dtor;

    FunctionInfo* ctor_info;
  };

  /////////////////////////////////

  struct StructInfo
  {
  };

  /////////////////////////////////

  struct EnumInfo
  {
  };

  /////////////////////////////////

  struct InterfaceInfo
  {
  };

  /////////////////////////////////
  struct ArrayInfo
  {
  };

  /////////////////////////////////

  struct Symbol
  {
    SymbolType  symbol_type;
    void*       meta_info;
  };

  /////////////////////////////////

  class SymbolTable
  {
  public:
    SymbolTable( SymbolTable* parent );

    bool    Check ( const std::string& symbol_name );
    void    Insert( const std::string& symbol_name, const Symbol& symbol );
    Symbol* LookUp( const std::string& symbol_name );

  private:
    // The parent scope. nullptr if none.
    SymbolTable* _parent_scope;

    // A list of all the child
    // scopes that are contained
    // within this one.
    std::vector<SymbolTable> _child_scopes;

    // The symbols that this scope contains.
    std::unordered_map<std::string, Symbol> _symbols;
  };

} }

#endif // PNL_SYMBOL_TABLE_H
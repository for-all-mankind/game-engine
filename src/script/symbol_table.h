#ifndef ICE_SCRIPT_SYMBOL_TABLE_H
#define ICE_SCRIPT_SYMBOL_TABLE_H

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
    OBJECT,
    STRUCT,
    ENUM,
    INTERFACE,
    ARRAY,
    TYPE,
  };

  /////////////////////////////////

  struct TypeInfo
  {
    std::string type_name;
    std::string alias_for;
  };

  /////////////////////////////////

  struct VariableInfo
  {
    std::string name;
    std::string type;
    std::string value;

    bool is_const;
  };

  /////////////////////////////////

  struct FunctionInfo
  {
    std::string name;
    TypeInfo    return_type;

    std::vector<VariableInfo> args;
  };

  /////////////////////////////////

  struct CtorInfo
  {
    std::string name;

    bool is_static;
    bool is_private;

    std::vector<VariableInfo> args;
  };

  struct DtorInfo
  {
    std::string name;

    bool is_private;
  };

  struct MethodInfo : public FunctionInfo
  {
    bool is_const;
    bool is_static;
    bool is_private;
  };

  struct MemberInfo : public VariableInfo
  {
    bool is_static;
    bool is_private;
  };

  struct DelegateInfo
  {
    std::string name;

    MemberInfo* delgate;
  };

  /////////////////////////////////

  struct ClassInfo
  {
    std::string name;

    bool has_ctor;
    bool has_dtor;

    CtorInfo ctor_info;
    DtorInfo dtor_info;

    std::vector<MethodInfo>   methods;
    std::vector<MemberInfo>   members;
    std::vector<DelegateInfo> delegates;
  };

  /////////////////////////////////

  struct ObjectInfo
  {
    std::string name;

    bool has_ctor;
    bool has_dtor;

    CtorInfo ctor_info;
    DtorInfo dtor_info;

    std::vector<MethodInfo>   methods;
    std::vector<MemberInfo>   members;
    std::vector<DelegateInfo> delegates;
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
    u32 size;
  };

  /////////////////////////////////

  struct Symbol
  {
    SymbolType type;
    void*      info;
  };

  /////////////////////////////////

  class SymbolTable
  {
  public:
    SymbolTable( SymbolTable* parent );
    ~SymbolTable();

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

#endif // ICE_SCRIPT_SYMBOL_TABLE_H
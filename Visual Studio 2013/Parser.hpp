#ifndef ICE_SCRIPT_PARSER_H
#define ICE_SCRIPT_PARSER_H

#include "Types.hpp"

#include "SymbolTable.hpp"
#include "Ast.hpp"
#include "Lexer.hpp"

namespace Ice { namespace Script {

  class Parser
  {
  public:
    Parser( SymbolTable* global );

    void Run( const std::string& filename );

  private:
    void BuildTypeTable();

    void Block();
    void IOStmt();
    void ImportStmt();
    void ExportStmt();
    void TopStmt();
    void FuncDeclStmt();
    void FuncDeclHead();
    void FuncArg();
    void Type();
    void TypeFuncPtr();
    void ierfaceDeclStmt();
    void ClassDeclStmt();
    void ObjectDeclStmt();
    void StructDeclStmt();
    void EnumDeclStmt();
    void TypeDeclStmt();
    void Stmt();
    void AnonScope();
    void VarAssignStmt();
    void ConstDeclInferStmt();
    void VarDeclAssignStmt();
    void VarDeclInferStmt();
    void VarDeclStmt();
    void TopExpr();

    bool Match ( TokenType match_type  );
    void    Expect( TokenType expect_type );

  private:
    SymbolTable* _global;
    Lexer        _lexer;
  };

} }

#endif // ICE_SCRIPT_PARSER_H
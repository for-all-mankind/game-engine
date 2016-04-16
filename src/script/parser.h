#ifndef ICE_SCRIPT_PARSER_H
#define ICE_SCRIPT_PARSER_H

#include "symbol_table.h"
#include "type_table.h"
#include "ast.h"
#include "lexer.h"

namespace Ice { namespace Script {

  class Parser
  {
  public:
    Parser( SymbolTable* global );

    Ast::Node* Run( const std::string& filename );

  private:
    void BuildTypeTable();

    void Block  ( Scope* scope );
    void IOStmt ( Scope* scope );
    void TopStmt( Scope* scope );
    void Stmt   ( Scope* scope );

    bool Match ( TokenType match_type  );
    void Expect( TokenType expect_type );

  private:
    SymbolTable* _global;
    Lexer        _lexer;

    TypeTable _type_table;
  };

} }

#endif // ICE_SCRIPT_PARSER_H
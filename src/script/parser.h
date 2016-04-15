#ifndef PNL_PARSER_H
#define PNL_PARSER_H

#include "symbol_table.h"
#include "ast.h"
#include "lexer.h"

#include <memory>

namespace Ice { namespace Script {



  class Parser
  {
  public:
    Parser( SymbolTable* global );

    void Run( const std::string& filename );

  private:


  private:
    SymbolTable* _global;

    Lexer _lexer;
  };

} }

#endif // PNL_PARSER_H
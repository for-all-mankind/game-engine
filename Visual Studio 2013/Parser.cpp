#include "Parser.hpp"
#include "Common.hpp"
namespace Ice { namespace Script {

  Parser::Parser( SymbolTable* global )
  {
    _global = global;

    // Register the built-in types.
    // _global->Insert( "byte"   );
    // _global->Insert( "short"  );
    // _global->Insert( "int"    );
    // _global->Insert( "long"   );
    // _global->Insert( "ubyte"  );
    // _global->Insert( "ushort" );
    // _global->Insert( "uint"   );
    // _global->Insert( "ulong"  );
    // _global->Insert( "float"  );
    // _global->Insert( "double" );
    // _global->Insert( "bool"   );
    // _global->Insert( "char"   );
    // _global->Insert( "string" );
  }

  void Parser::Run( const std::string& filename )
  {
    // Scan the input file.
    _lexer.Run( filename );

    /*
      program ::= io_stmt_list TOK_EOF .

      io_stmt_list ::= io_stmt_list io_stmt .
      io_stmt_list ::= io_stmt .
      io_stmt_list ::= .
    */

    while ( !Match( TOK_EOF ) )
      IOStmt();
  }

  /////////////////////////////////

  void Parser::Block()
  {
    /*
      block ::= stmt_list KW_END .

      stmt_list ::= stmt_list stmt .
      stmt_list ::= stmt .
    */

    while ( !Match( KW_END ) )
      Stmt();
  }

  /////////////////////////////////

  void Parser::IOStmt()
  {
    /*
      io_stmt ::= import_stmt .
      io_stmt ::= export_stmt .
      io_stmt ::= top_stmt .
    */

    if ( Match( KW_IMPORT ) )
      ImportStmt();

    else if ( Match( KW_EXPORT ) )
      ExportStmt();

    else
      TopStmt();
  }

  /////////////////////////////////

  void Parser::ImportStmt()
  {
    /*
      import_stmt ::= KW_IMPORT LIT_STRING as_namespace TOK_SEMI_COLON .

      as_namespace ::= KW_AS TOK_IDENTIFIER .
      as_namespace ::= .
    */

    Expect( LIT_STRING );

    if ( Match( KW_AS ) )
      Expect( TOK_IDENTIFIER );

    Expect( TOK_SEMI_COLON );
  }


  /////////////////////////////////

  void Parser::ExportStmt()
  {
    /*
      export_stmt ::= KW_EXPORT top_stmt .
    */

    TopStmt();
  }

  /////////////////////////////////

  void Parser::TopStmt()
  {
    /*
      top_stmt ::= func_decl_stmt .
      top_stmt ::= interface_decl_stmt .
      top_stmt ::= class_decl_stmt .
      top_stmt ::= obj_decl_stmt .
      top_stmt ::= struct_decl_stmt .
      top_stmt ::= namespace_decl_stmt .
      top_stmt ::= enum_decl_stmt .
      top_stmt ::= type_decl_stmt .
      top_stmt ::= stmt .
    */

    const Token* t1 = _lexer.PeekToken( 0 );
    const Token* t2 = _lexer.PeekToken( 1 );
    const Token* t3 = _lexer.PeekToken( 2 );

    if ( t1 == nullptr )
      ; // TODO: complain...

    if ( t1->type == TOK_IDENTIFIER )
    {
      if ( t2 == nullptr )
        ; // TODO: complain...

      if ( t2->type == TOK_COLON )
      {
        if ( t3 == nullptr )
          ; // TODO: complain...

        if ( t3->type == KW_FUNC )
          FuncDeclStmt();

        else if ( t3->type == KW_INTERFACE )
          ierfaceDeclStmt();

        else if ( t3->type == KW_CLASS )
          ClassDeclStmt();

        else if ( t3->type == KW_OBJECT )
          ObjectDeclStmt();

        else if ( t3->type == KW_STRUCT )
          StructDeclStmt();

        else if ( t3->type == KW_ENUM )
          EnumDeclStmt();

        else if ( t3->type == KW_TYPE )
          TypeDeclStmt();

        else
          VarDeclStmt();
      }

      Stmt();
    }
    else if ( t1->type == KW_SCOPE )
      AnonScope();
    else
      ; // TODO: complain...
  }

  /////////////////////////////////

  void Parser::FuncDeclStmt()
  {
    /*
      func_decl_stmt ::= func_decl_head block KW_END .
    */

    FuncDeclHead();
    Block();
  }

  void Parser::FuncDeclHead()
  {
    /*
      func_decl_head ::= TOK_IDENTIFIER TOK_COLON KW_FUNC TOK_LPAREN func_args TOK_RPAREN TOK_FUNC_ARROW type

      func_args ::= func_args_list .
      func_args ::= .

      func_args_list ::= func_args_list TOK_COMMA func_arg .
      func_args_list ::= func_arg .
    */

    Expect( TOK_IDENTIFIER );
    Expect( TOK_COLON );
    Expect( KW_FUNC );
    Expect( TOK_LPAREN );

    while ( !Match( TOK_RPAREN ) )
    {
      FuncArg();
      Match( TOK_COMMA );
    }

    Expect( TOK_RPAREN );

    Expect( TOK_FUNC_ARROW );

    Type();
  }

  void Parser::FuncArg()
  {
    /*
      func_arg ::= TOK_IDENTIFIER TOK_COLON       type .
      func_arg ::= TOK_IDENTIFIER TOK_COLON_COLON type .
    */

    Expect( TOK_IDENTIFIER );

    if ( Match( TOK_COLON ) )
      ;
    else
      Expect( TOK_COLON_COLON );

    Type();
  }

  /////////////////////////////////

  void Parser::Type()
  {
    /*
      type ::= TOK_IDENTIFIER .
      type ::= TOK_IDENTIFIER TOK_LT type TOK_GT .
      type ::= TOK_CARET type .
    */

    if ( Match( TOK_CARET ) )
      Type();
    else
      Expect( TOK_IDENTIFIER );

    if ( Match( TOK_LT ) )
    {
      Type();
      Expect( TOK_GT );
    }
  }

  /////////////////////////////////

  void Parser::TypeFuncPtr()
  {
    /*
      type ::= TOK_CARET KW_FUNC TOK_LPAREN type_args_list TOK_RPAREN TOK_FUNC_ARROW type .

      type_args_list ::= type_args_list type_arg .
      type_args_list ::= type_arg .

      type_arg ::= type TOK_COMMA .
      type_arg ::= type .
    */

    Expect( TOK_CARET  );
    Expect( KW_FUNC    );
    Expect( TOK_LPAREN );

    while ( !Match( TOK_RPAREN ) )
    {
      Type();

      if ( Match( TOK_RPAREN ) )
        break;
      else
        Expect( TOK_COMMA );
    }

    Expect( TOK_RPAREN );

    Expect( TOK_FUNC_ARROW );

    Type();
  }

  /////////////////////////////////

  void Parser::ierfaceDeclStmt()
  {
    /*
      interface_stmt_decl ::= TOK_IDENTIFIER TOK_COLON KW_INTERFACE interface_body KW_END .

      interface_body ::= func_head_list .
      interface_body ::= .

      func_head_list ::= func_head_list TOK_SEMI_COLON func_decl_head .
      func_head_list ::= func_decl_head TOK_SEMI_COLON .
    */

    Expect( TOK_IDENTIFIER );
    Expect( TOK_COLON );
    Expect( KW_INTERFACE );

    while ( !Match( KW_END ) )
    {
      FuncDeclHead();
      Expect( TOK_SEMI_COLON );
    }
  }

  /////////////////////////////////

  void Parser::ClassDeclStmt()
  {
    /*

    */

  }

  /////////////////////////////////

  void Parser::ObjectDeclStmt()
  {
    /*
      obj_decl_stmt ::= TOK_IDENTIFIER TOK_COLON KW_OBJECT obj_body KW_END .

      obj_body ::= obj_stmt_list .
      obj_body ::= .

      obj_stmt_list ::= obj_stmt_list obj_stmt .
      obj_stmt_list ::= obj_stmt .

      obj_stmt ::= var_decl_infer_stmt TOK_SEMI_COLON .
      obj_stmt ::= member_decl_stmt TOK_SEMI_COLON .
      obj_stmt ::= member_decl_assign_stmt TOK_SEMI_COLON .
      obj_stmt ::= method_decl_stmt .
      obj_stmt ::= delegate_stmt .
    */


  }

  /////////////////////////////////

  void Parser::StructDeclStmt()
  {
    /*
      struct_stmt_decl ::= TOK_IDENTIFIER TOK_COLON KW_STRUCT struct_body KW_END .

      struct_body ::= var_decl_list .
      struct_body ::= .

      var_decl_list ::= var_decl_list TOK_SEMI_COLON var_decl .
      var_decl_list ::= var_decl .
    */

    Expect( TOK_IDENTIFIER );
    Expect( TOK_COLON );
    Expect( KW_STRUCT );

    while ( !Match( KW_END ) )
    {
      VarDeclStmt();
      Expect( TOK_SEMI_COLON );
    }
  }

  /////////////////////////////////

  void Parser::EnumDeclStmt()
  {
    /*
      enum_decl_stmt ::= TOK_IDENTIFIER TOK_COLON KW_ENUM enum_body KW_END .

      enum_body ::= identifier_list .
      enum_body ::= .

      identifier_list ::= identifier_list TOK_COMMA TOK_IDENTIFIER .
      identifier_list ::= TOK_IDENTIFIER .
    */

    Expect( TOK_IDENTIFIER );
    Expect( TOK_COLON      );
    Expect( KW_ENUM        );

    while ( !Match( KW_END ) )
    {
      Expect( TOK_IDENTIFIER );

      if ( Match( KW_END ) )
        break;
      else
        Expect( TOK_COMMA );
    }
  }

  /////////////////////////////////

  void Parser::TypeDeclStmt()
  {
    /*
      type_decl_stmt ::= TOK_IDENTIFIER TOK_COLON KW_TYPE type TOK_SEMI_COLON
    */

    Expect( TOK_IDENTIFIER );
    Expect( TOK_COLON      );
    Expect( KW_TYPE        );

    Type();

    Expect( TOK_SEMI_COLON );
  }

  /////////////////////////////////

  void Parser::Stmt()
  {
    /*
      stmt ::= anon_scope .
      stmt ::= var_assign_stmt .
      stmt ::= const_decl_infer_stmt .
      stmt ::= var_decl_stmt .
      stmt ::= var_decl_infer_stmt .
      stmt ::= var_decl_assign_stmt .
      stmt ::= top_expr .
    */

    const Token* t = _lexer.PeekToken( 0 );

    if ( t->type == KW_SCOPE )
      AnonScope();

    else if ( t->type == TOK_IDENTIFIER )
    {
      const Token* t = _lexer.PeekToken( 1 );

      if ( t->type == TOK_EQUAL )
        VarAssignStmt();

      else if ( t->type == TOK_COLON_COLON )
        ConstDeclInferStmt();

      else if ( t->type == TOK_COLON_EQUAL )
        VarDeclInferStmt();

      else if ( t->type == TOK_COLON )
        VarDeclAssignStmt(); // May return a 'VarDeclStmt'

      else
        TopExpr();
    }

    else
      ; // TODO: complain...
  }

  /////////////////////////////////

  void Parser::AnonScope()
  {
    /*
      anon_scope ::= KW_SCOPE block KW_END .
    */

    Expect( KW_SCOPE );

    Block();
  }

  /////////////////////////////////

  void Parser::VarAssignStmt()
  {
    /*

    */
  }

  /////////////////////////////////

  void Parser::ConstDeclInferStmt()
  {

  }

  /////////////////////////////////

  void Parser::VarDeclInferStmt()
  {

  }

  /////////////////////////////////

  void Parser::VarDeclAssignStmt()
  {

  }

  /////////////////////////////////

  void Parser::VarDeclStmt()
  {

  }

  /////////////////////////////////

  void Parser::TopExpr()
  {

  }

  /////////////////////////////////

  bool Parser::Match( TokenType match_type )
  {
    const Token* token = _lexer.PeekToken( 0 );

    if ( token->type == match_type )
    {
      _lexer.NextToken();
      return true;
    }

    return false;
  }

  void Parser::Expect( TokenType expect_type )
  {
    if ( !Match( expect_type ) )
    {
      // TODO: complain...
    }
  }

} }
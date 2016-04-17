#include "parser.h"

#include <iostream>

namespace Ice { namespace Script {

  Parser::Parser( SymbolTable* global )
  {
    _global = global;

    // Register the built-in types.
    // _global->Insert( "Int8"   );
    // _global->Insert( "Int16"  );
    // _global->Insert( "Int32"  );
    // _global->Insert( "Int64"  );
    // _global->Insert( "UInt8"  );
    // _global->Insert( "UInt16" );
    // _global->Insert( "UInt32" );
    // _global->Insert( "UInt64" );
    // _global->Insert( "Float"  );
    // _global->Insert( "Double" );
    // _global->Insert( "Bool"   );
    // _global->Insert( "Char"   );
    // _global->Insert( "String" );

    // _global->Insert( "Int" , "Int32"  );
    // _global->Insert( "UInt", "UInt32" );
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

    if ( t1 == nullptr
      || t2 == nullptr
      || t3 == nullptr );
      // TODO: complain...

    if ( t1->type == TOK_IDENTIFIER )
    {
      if ( t2->type == TOK_COLON )
      {
        if ( t3->type == KW_FUNC )
          FuncDeclStmt();

        else if ( t3->type == KW_INTERFACE )
          InterfaceDeclStmt();

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
    else
    {
      // TODO: complain...
    }
  }

  /////////////////////////////////

  void Parser::FuncDeclStmt()
  {
    /*
      func_decl_stmt ::= func_decl_head block KW_END .

      func_decl_head ::= TOK_IDENTIFIER TOK_COLON KW_FUNC TOK_LPAREN func_args TOK_RPAREN TOK_FUNC_ARROW type

      func_args ::= func_args_list .
      func_args ::= .

      func_args_list ::= func_args_list func_arg .
      func_args_list ::= func_arg .

      func_arg ::= var_decl TOK_COMMA .
      func_arg ::= var_decl .
    */

    FuncDeclHead();
    Block();
  }

  void Parser::FuncDeclHead()
  {
    Expect( TOK_IDENTIFIER );
    Expect( TOK_COLON );
    Expect( KW_FUNC );
    Expect( TOK_LPAREN );

    while ( !Match( TOK_RPAREN ) )
    {
      VarDeclStmt();
      Match( TOK_COMMA );
    }

    Expect( TOK_RPAREN );

    Expect( TOK_FUNC_ARROW );

    Type();
  }

  /////////////////////////////////

  void Parser::Type()
  {
    /*
      type ::= TOK_IDENTIFIER .
      type ::= TOK_LSQUARE LIT_INT TOK_RSQUARE type .
      type ::= TOK_CARET TOK_IDENTIFIER .
    */

    if ( Match( TOK_IDENTIFIER ) )
      ; // TODO: lookup type.
    else if ( Match( TOK_LSQUARE ) )
    {
      Expect( LIT_INT     );
      Expect( TOK_RSQUARE );
      Type();
    }
    else
    {
      Expect( TOK_CARET      );
      Expect( TOK_IDENTIFIER );
    }
  }

  void Parser::FuncPtrType()
  {
    /*
      type ::= TOK_CARET KW_FUNC TOK_LPAREN type_args_list TOK_RPAREN TOK_FUNC_ARROW type .

      type_args_list ::= type_args_list type_arg .
      type_args_list ::= type_arg .

      type_arg ::= type TOK_COMMA .
      type_arg ::= type .
    */

    Expect( KW_FUNC    );
    Expect( TOK_LPAREN );

    while ( !Match( TOK_RPAREN ) )
    {
      Type();
      Match( TOK_COMMA );
    }

    Expect( TOK_RPAREN );

    Expect( TOK_FUNC_ARROW );

    Type();
  }

  /////////////////////////////////

  void Parser::InterfaceDeclStmt()
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

    if ( Match( TOK_DOLLAR ) )
    {

    }
    else
    {

    }

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

    if ( Match( TOK_IDENTIFIER ) )
      ; // TODO: do something...
    while ( !Match( KW_END ) )
    {
      Expect( TOK_COMMA );

      if ( Match( TOK_IDENTIFIER ) )
        ; // TODO: do something...
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
      stmt ::= var_assign_stmt .
      stmt ::= var_decl_stmt .
      stmt ::= var_decl_infer_stmt .
      stmt ::= var_decl_assign_stmt .
      stmt ::= top_expr .
    */

    if ( _lexer.PeekToken( 0 )->type == TOK_IDENTIFIER );
    {
      const Token* t = _lexer.PeekToken( 1 );

      if ( t->type == TOK_EQUAL );
        VarAssignStmt();

      else if ( t->type == TOK_COLON_EQUAL );
        VarDeclInferStmt();

      else if ( t->type == TOK_COLON );
        VarDeclAssignStmt(); // May return a 'VarDeclStmt'

      else;
        TopExpr();
    }
  }

  /////////////////////////////////

  void VarAssignStmt()
  {

  }

  /////////////////////////////////

  void Parser::VarDeclStmt()
  {

  }

  /////////////////////////////////

  void Parser::VarDeclAssignStmt()
  {

  }

  /////////////////////////////////

  void Parser::VarDeclInferStmt()
  {

  }

  /////////////////////////////////
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
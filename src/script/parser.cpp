#include "parser.h"

#include <iostream>

namespace Ice { namespace Script {

  Parser::Parser( SymbolTable* global )
  {
    _global = global;

    // Register the built-in types.
    _type_table.Add( "Int8"   );
    _type_table.Add( "Int16"  );
    _type_table.Add( "Int32"  );
    _type_table.Add( "Int64"  );
    _type_table.Add( "UInt8"  );
    _type_table.Add( "UInt16" );
    _type_table.Add( "UInt32" );
    _type_table.Add( "UInt64" );
    _type_table.Add( "Float"  );
    _type_table.Add( "Double" );
    _type_table.Add( "Bool"   );
    _type_table.Add( "Char"   );
    _type_table.Add( "String" );

    _type_table.Alias( "Int" , "Int32"  );
    _type_table.Alias( "UInt", "UInt32" );
  }

  void Parser::Run( const std::string& filename )
  {

    // Scan the input file.
    _lexer.Run( filename );

    // First pass to populate the type table
    // with user defined types.
    PopulateTypeTable();

    // Parse the program.

    /*
      program ::= io_stmt_list TOK_EOF .

      io_stmt_list ::= io_stmt_list io_stmt .
      io_stmt_list ::= io_stmt .
      io_stmt_list ::= .
    */

    while ( !Match( TOK_EOF ) )
      IOStmt( table );
  }

  /////////////////////////////////

  void Parser::PopulateTypeTable()
  {
    while ( true )
    {
      const Token* c  = _lexer.NextToken();
      const Token* n1 = _lexer.PeekToken( 1 );
      const Token* n2 = _lexer.PeekToken( 2 );

      if ( c->type == TOK_EOF )
        break;

      if ( c->type == TOK_IDENTIFIER && n1->type == TOK_COLON )
      {
        switch ( n2->type )
        {
          case KW_INTERFACE:
          case KW_CLASS:
          case KW_STRUCT:
          case KW_ENUM:
            if ( !_type_table.Check( c->lexeme ) )
              _type_table.Add( c->lexeme );
            else
              // TODO: add line numbers.
              std::cout << "Redefinition of " << c->lexeme << std::endl;
            break;

          case KW_TYPE:
            // TODO: Get the right hand type.
            // _type_table.Check( )
            break;

          default:
            break;
        }
      }
    }

    _lexer.Reset();
  }

  /////////////////////////////////

  void Parser::Block( Scope* scope )
  {
    /*
      block ::= stmt_list KW_END .

      stmt_list ::= stmt_list stmt .
      stmt_list ::= stmt .
    */

    while ( !Match( KW_END ) )
      Stmt( table );
  }

  /////////////////////////////////

  void Parser::IOStmt( Scope* scope )
  {
    /*
      io_stmt ::= import_stmt .
      io_stmt ::= export_stmt .
      io_stmt ::= top_stmt .
    */

    if ( Match( KW_IMPORT ) )
      Import( scope );

    else if ( Match( KW_EXPORT ) )
      Export( scope );

    else
      TopStmt( scope );
  }

  /////////////////////////////////

  void Parser::ImportStmt( Scope* scope )
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

  void Parser::ExportStmt( Scope* scope )
  {
    /*
      export_stmt ::= KW_EXPORT top_stmt .
    */

    TopStmt( scope );
  }

  /////////////////////////////////

  void Parser::TopStmt( Scope* scope )
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
      || t3 == nullptr )
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

        else if ( t3->type == KW_NAMESPACE )
          NamespaceDeclStmt();

        else if ( t3->type == KW_ENUM )
          EnumDeclStmt();

        else if ( t3->type == KW_TYPE )
          TypeDeclStmt();

        else
          // TODO: complain...
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
      type ::= TOK_CARET KW_FUNC TOK_LPAREN type_args_list TOK_RPAREN TOK_FUNC_ARROW type .

      type_args_list ::= type_args_list type_arg .
      type_args_list ::= type_arg .

      type_arg ::= type TOK_COMMA .
      type_arg ::= type .
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
      Expect( TOK_CARET  );

      if ( Match( TOK_INDETIFIER ) )
        ; // TODO: lookup type.
      else
      {
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
    }
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
      obj_decl_stmt ::= TOK_INDETIFIER TOK_COLON KW_OBJECT obj_body KW_END .

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

  void Parser::NamespaceDeclStmt()
  {
    /*
      namespace_decl_stmt ::= TOK_IDENTIFIER TOK_COLON KW_NAMESPACE top_stmt_list KW_END .

      top_stmt_list ::= top_stmt_list top_stmt .
      top_stmt_list ::= top_stmt .
    */

    Expect( TOK_IDENTIFIER );
    Expect( TOK_COLON      );
    Expect( KW_NAMESPACE   );

    while ( !Match( KW_END ) )
      TopStmt();
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

  void Parser::Stmt( Scope* scope )
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

      if ( t->type == TOK_EQUAL )
        VarAssignStmt();

      else if ( t->type == TOK_COLON_EQUAL )
        VarDeclInferStmt();

      else if ( t->type == TOK_COLON )
        VarDeclAssignStmt(); // May return a 'VarDeclStmt'

      else
        TopExpr();
    }
  }

  /////////////////////////////////

  const Token* Parser::Current()
  {
    return _lexer.PeekToken( 0 );
  }

  bool Match( TokenType match_type )
  {
    const Token* token = _lexer.PeekToken( 0 );

    if ( token->type == match_type )
    {
      _lexer.NextToken();
      return true;
    }

    return false;
  }

  void Expect( TokenType expect_type )
  {
    if ( !Match( expect_type ) )
    {
      // TODO: complain...
    }
  }

} }
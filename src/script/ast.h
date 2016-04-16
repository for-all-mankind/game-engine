#ifndef ICE_SCRIPT_AST_H
#define ICE_SCRIPT_AST_H

#include "../util/types.h"

#include <vector>

namespace Ice { namespace Script { namespace Ast {

  class Node;
    class Block;
    class Stmt;
      class ImportStmt;
      class ExportStmt;
      class ClassDeclStmt;
      class FuncDeclStmt;
      class InterfaceDeclStmt;
      class StructDeclStmt;
      class TypeDeclStmt;
      class NamespaceDeclStmt;
      class ObjectDeclStmt;
      class EnumDeclStmt;
      class AssignStmt;
      class VarDeclStmt;
    class Expr;
      class ByteExpr;
      class ShortExpr;
      class IntExpr;
      class LongExpr;
      class UByteExpr;
      class UShortExpr;
      class UIntExpr;
      class ULongExpr;
      class StringExpr;
      class CharExpr;
      class BooleanExpr;

  /////////////////////////////////

  class Node
  {
  public:
             Node() {}
    virtual ~Node() {};

    virtual void PrintSelf() const = 0;
    virtual void PrintTree() const = 0;

    virtual void GenerateCode() = 0;

  protected:
    Node* _parent;
  };

  /////////////////////////////////

  class Block : public Node
  {
  public:
    Block( std::vector<Stmt> stmts )
      : _stmts( std::move( stmts ) )
    {}

    virtual ~Block() {}

  private:
    std::vector<Stmt> _stmts;
  };

  /////////////////////////////////

  class Stmt : public Node
  {
  public:
    Stmt();
    virtual ~Stmt();

  private:

  };

  /////////////////////////////////

  class Expr : public Node
  {
  public:
    Expr();
    virtual ~Expr();

  private:

  };

  /////////////////////////////////

  class ByteExpr : public Expr
  {
  public:
    ByteExpr( i8 value )
      : _value( value )
    {}

  private:
    i8 _value;
  };

  /////////////////////////////////

  class ShortExpr : public Expr
  {
  public:
    ShortExpr( i16 value )
      : _value( value )
    {}

  private:
    i16 _value;
  };

  /////////////////////////////////

  class IntExpr : public Expr
  {
  public:
    IntExpr( i32 value )
      : _value( value )
    {}

  private:
    i32 _value;
  };

  /////////////////////////////////

  class LongExpr : public Expr
  {
  public:
    LongExpr( i64 value )
      : _value( value )
    {}

  private:
    i64 _value;
  };

  /////////////////////////////////

  class UByteExpr : public Expr
  {
  public:
    UByteExpr( u8 value )
      : _value( value )
    {}

  private:
    u8 _value;
  };

  /////////////////////////////////

  class UShortExpr : public Expr
  {
  public:
    UShortExpr( u16 value )
      : _value( value )
    {}

  private:
    u16 _value;
  };

  /////////////////////////////////

  class UIntExpr : public Expr
  {
  public:
    UIntExpr( u32 value )
      : _value( value )
    {}

  private:
    u32 _value;
  };

  /////////////////////////////////

  class ULongExpr : public Expr
  {
  public:
    ULongExpr( u64 value )
      : _value( value )
    {}

  private:
    u64 _value;
  };

  /////////////////////////////////

  class StringExpr : public Expr
  {
  public:
    StringExpr( std::string value )
      : _value( value )
    {}

  private:
    std::string _value;
  };

  /////////////////////////////////

  class CharExpr : public Expr
  {
  public:
    CharExpr( i16 value )
      : _value( value )
    {}

  private:
    i16 _value;
  };

  /////////////////////////////////

  class BooleanExpr : public Expr
  {
  public:
    BooleanExpr( bool value )
      : _value( value )
    {}

  private:
    bool _value;
  };

} } }

#endif // ICE_SCRIPT_AST_H
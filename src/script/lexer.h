#ifndef PNL_LEXER_H
#define PNL_LEXER_H

#include "../util/types.h"
#include "token.h"

#include <string>
#include <vector>
#include <stack>

namespace Ice { namespace Script {

  struct LexerMode;
  struct LexerState;
  class  Lexer;

  /////////////////////////////////

  struct LexerMode
  {
    // The lexing function that this struct contains.
    // It returns a pointer to another struct containing
    // a similar function.
    LexerMode* (*Func)( Lexer* );

    // Equality checks.
    bool operator==( const LexerMode& other ) const;
    bool operator!=( const LexerMode& other ) const;

    // All the lexing states have beed defined
    // here, but the actual function definitions
    // live in lexer.cpp.
    static LexerMode Start;
    static LexerMode End;
    static LexerMode Identifier;
    static LexerMode Punctuation;
    static LexerMode SkipLineComment;
    static LexerMode SkipBlockComment;
    static LexerMode SkipSpace;
    static LexerMode String;
    static LexerMode Char;
    static LexerMode Number;
    static LexerMode HexNumber;
    static LexerMode BinNumber;
  };

  /////////////////////////////////

  struct LexerState
  {
    i32 char_index = -1;

    i32 line   = 1;
    i32 column = 1;

    LexerMode* mode;

    std::string filename;
    std::string source;

    std::stack<u32> line_lengths;
  };

  /////////////////////////////////

  class Lexer
  {
  public:
    void Run( const std::string& filename );

    const Token* NextToken();
          void   PrevToken();

    char NextChar();
    char PeekChar( i32 n );

    void AddToken( const std::string& lexeme, TokenType type );

  private:
    // void ReadFile();

    void StateStore();
    bool StateRestore();

  private:
    LexerState* _state;

    i32 _token_index = -1;

    std::vector<Token>      _tokens;
    std::stack <LexerState> _states;
  };

} }

#endif // PNL_LEXER_H
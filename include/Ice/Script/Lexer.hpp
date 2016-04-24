#ifndef ICE_SCRIPT_LEXER_H
#define ICE_SCRIPT_LEXER_H

#include <Ice/Common/Types.hpp>
#include <Ice/Script/Token.hpp>

#include <vector>
#include <stack>

namespace Ice { namespace Script {

  class Lexer;

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
    static LexerMode OctNumber;
  };

  /////////////////////////////////

  class Lexer
  {
  public:
    void Run( const std::string& filename );
    void Reset();

    const Token* NextToken();
    const Token* PeekToken( i32 n );

    char NextChar();
    char PeekChar( i32 n );

    void AddToken( const std::string& lexeme, TokenType type );

  private:
    i32 _char_index = -1;

    i32 _line   = 1;
    i32 _column = 1;

    LexerMode* _mode;

    std::string _filename;
    std::string _source;

    std::stack<u32> _line_lengths;

    i32 _token_index = -1;

    std::vector<Token> _tokens;
  };

} }

#endif // ICE_SCRIPT_LEXER_H
#include <Ice/Common/File.hpp>
#include <Ice/Script/Lexer.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

namespace Ice { namespace Script {

  /////////////////////////////////
  // The individual lexing functions.

  LexerMode* mode_start( Lexer* lexer )
  {
    char c = lexer->PeekChar( 1 );

    if ( c == '\0' )
      return &LexerMode::End;

    else if ( isspace( c ) )
      return &LexerMode::SkipSpace;

    else if ( isalpha( c ) || c == '_' )
      return &LexerMode::Identifier;

    else if ( isdigit( c ) )
      return &LexerMode::Number;

    else if ( c == '"' )
      return &LexerMode::String;

    else if ( c == '\'' )
      return &LexerMode::Char;

    else if ( ispunct( c ) )
      return &LexerMode::Punctuation;

    else
      return &LexerMode::End;
  }

  /////////////////////////////////

  LexerMode* mode_end( Lexer* lexer )
  {
    lexer->AddToken( "eof", TOK_EOF );

    return &LexerMode::End;
  }

  /////////////////////////////////

  LexerMode* mode_identifier( Lexer* lexer )
  {
    std::string buffer;
    char        c;

    while ( true )
    {
      c = lexer->PeekChar( 1 );

      if ( isalnum( c ) || c == '_' )
      {
        buffer += c;
        lexer->NextChar();
        continue;
      }

      break;
    }

    // Keywords
    if      ( buffer == "borrow"    ) lexer->AddToken( buffer, KW_BORROW    );
    else if ( buffer == "cast"      ) lexer->AddToken( buffer, KW_CAST      );
    else if ( buffer == "import"    ) lexer->AddToken( buffer, KW_IMPORT    );
    else if ( buffer == "from"      ) lexer->AddToken( buffer, KW_FROM      );
    else if ( buffer == "using"     ) lexer->AddToken( buffer, KW_USING     );
    else if ( buffer == "as"        ) lexer->AddToken( buffer, KW_AS        );
    else if ( buffer == "func"      ) lexer->AddToken( buffer, KW_FUNC      );
    else if ( buffer == "return"    ) lexer->AddToken( buffer, KW_RETURN    );
    else if ( buffer == "struct"    ) lexer->AddToken( buffer, KW_STRUCT    );
    else if ( buffer == "enum"      ) lexer->AddToken( buffer, KW_ENUM      );
    else if ( buffer == "class"     ) lexer->AddToken( buffer, KW_CLASS     );
    else if ( buffer == "object"    ) lexer->AddToken( buffer, KW_OBJECT    );
    else if ( buffer == "this"      ) lexer->AddToken( buffer, KW_THIS      );
    else if ( buffer == "static"    ) lexer->AddToken( buffer, KW_STATIC    );
    else if ( buffer == "interface" ) lexer->AddToken( buffer, KW_INTERFACE );
    else if ( buffer == "delegate"  ) lexer->AddToken( buffer, KW_DELEGATE  );
    else if ( buffer == "type"      ) lexer->AddToken( buffer, KW_TYPE      );
    else if ( buffer == "new"       ) lexer->AddToken( buffer, KW_NEW       );
    else if ( buffer == "delete"    ) lexer->AddToken( buffer, KW_DELETE    );
    else if ( buffer == "owner"     ) lexer->AddToken( buffer, KW_OWNER     );
    else if ( buffer == "view"      ) lexer->AddToken( buffer, KW_VIEW      );
    else if ( buffer == "scope"     ) lexer->AddToken( buffer, KW_SCOPE     );
    else if ( buffer == "end"       ) lexer->AddToken( buffer, KW_END       );
    else if ( buffer == "if"        ) lexer->AddToken( buffer, KW_IF        );
    else if ( buffer == "else"      ) lexer->AddToken( buffer, KW_ELSE      );
    else if ( buffer == "for"       ) lexer->AddToken( buffer, KW_FOR       );
    else if ( buffer == "in"        ) lexer->AddToken( buffer, KW_IN        );
    else if ( buffer == "while"     ) lexer->AddToken( buffer, KW_WHILE     );
    else if ( buffer == "break"     ) lexer->AddToken( buffer, KW_BREAK     );
    else if ( buffer == "continue"  ) lexer->AddToken( buffer, KW_CONTINUE  );
    // Literals
    else if ( buffer == "null"      ) lexer->AddToken( buffer, LIT_NULL      );
    else if ( buffer == "true"      ) lexer->AddToken( buffer, LIT_BOOLEAN   );
    else if ( buffer == "false"     ) lexer->AddToken( buffer, LIT_BOOLEAN   );
    // Identifiers
    else
      lexer->AddToken( buffer, TOK_IDENTIFIER );

    return &LexerMode::Start;
  }

  /////////////////////////////////

  LexerMode* mode_punctuation( Lexer* lexer )
  {
    char c = lexer->NextChar();

    if ( c == '(' )
      lexer->AddToken( "(", TOK_LPAREN );
    else if ( c == ')' )
      lexer->AddToken( ")", TOK_RPAREN );
    else if ( c == '{' )
      lexer->AddToken( "{", TOK_LCURLY );
    else if ( c == '}' )
      lexer->AddToken( "}", TOK_RCURLY );
    else if ( c == '[' )
      lexer->AddToken( "[", TOK_LSQUARE );
    else if ( c == ']' )
      lexer->AddToken( "]", TOK_RSQUARE );
    else if ( c == ';' )
      lexer->AddToken( ";", TOK_SEMI_COLON );
    else if ( c == '?' )
      lexer->AddToken( "?", TOK_QUESTION );
    else if ( c == '.' )
      lexer->AddToken( ".", TOK_DOT );
    else if ( c == '@' )
      lexer->AddToken( "@", TOK_AT );
    else if ( c == '$' )
      lexer->AddToken( "$", TOK_DOLLAR );
    else if ( c == ',' )
      lexer->AddToken( ",", TOK_COMMA );
    else if ( c == '~' )
      lexer->AddToken( "~", TOK_TILDE );
    else if ( c == '^' )
      lexer->AddToken( "^", TOK_CARET );
    else if ( c == '#' )
      lexer->AddToken( "#", TOK_CHANNEL );
    else if ( c == '=' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '=' )
      {
        lexer->AddToken( "==", TOK_EQUAL_EQUAL );
        lexer->NextChar();
      }
      else
        lexer->AddToken( "=", TOK_EQUAL );
    }
    else if ( c == ':' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '=' )
      {
        lexer->AddToken( ":=", TOK_COLON_EQUAL );
        lexer->NextChar();
      }
      else if ( n == ':' )
      {
        lexer->AddToken( "::", TOK_COLON_COLON );
        lexer->NextChar();
      }
      else
        lexer->AddToken( ":", TOK_COLON );
    }
    else if ( c == '>' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '=' )
      {
        lexer->AddToken( ">=", TOK_GT_EQUAL );
        lexer->NextChar();
      }
      else if ( n == '>' )
      {
        lexer->AddToken( ">>", TOK_RSHIFT );
        lexer->NextChar();
      }
      else
        lexer->AddToken( ">", TOK_GT );
    }
    else if ( c == '<' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '=' )
      {
        lexer->AddToken( "<=", TOK_LT_EQUAL );
        lexer->NextChar();
      }
      else if ( n == '-' )
      {
        lexer->AddToken( "<-", TOK_CHANNEL_ARROW );
        lexer->NextChar();
      }
      else if ( n == '<' )
      {
        lexer->AddToken( "<<", TOK_LSHIFT );
        lexer->NextChar();
      }
      else
        lexer->AddToken( "<", TOK_LT );
    }
    else if ( c == '!' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '=' )
      {
        lexer->AddToken( "!=", TOK_EXCLAMATION_EQUAL );
        lexer->NextChar();
      }
      else
        lexer->AddToken( "!", TOK_EXCLAMATION );
    }
    else if ( c == '&' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '&' )
      {
        lexer->AddToken( "&&", TOK_AMP_AMP );
        lexer->NextChar();
      }
      else
        lexer->AddToken( "&", TOK_AMP );
    }
    else if ( c == '|' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '|' )
      {
        lexer->AddToken( "||", TOK_PIPE_PIPE );
        lexer->NextChar();
      }
      else
        lexer->AddToken( "|", TOK_PIPE );
    }
    else if ( c == '%' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '=' )
      {
        lexer->AddToken( "%=", TOK_MODULO_EQUAL );
        lexer->NextChar();
      }
      else
        lexer->AddToken( "%", TOK_MODULO );
    }
    else if ( c == '+' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '=' )
      {
        lexer->AddToken( "+=", TOK_ADD_EQUAL );
        lexer->NextChar();
      }
      else if ( n == '+' )
      {
        lexer->AddToken( "++", TOK_INCREMENT );
        lexer->NextChar();
      }
      else
        lexer->AddToken( "+", TOK_ADD );
    }
    else if ( c == '-' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '=' )
      {
        lexer->AddToken( "-=", TOK_SUB_EQUAL );
        lexer->NextChar();
      }
      else if ( n == '-' )
      {
        lexer->AddToken( "--", TOK_DECREMENT );
        lexer->NextChar();
      }
      else if ( n == '>' )
      {
        lexer->AddToken( "->", TOK_FUNC_ARROW );
        lexer->NextChar();
      }
      else
        lexer->AddToken( "-", TOK_SUB );
    }
    else if ( c == '*' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '=' )
      {
        lexer->AddToken( "*=", TOK_MUL_EQUAL );
        lexer->NextChar();
      }
      else
        lexer->AddToken( "*", TOK_MUL );
    }
    else if ( c == '/' )
    {
      char n = lexer->PeekChar( 1 );

      if ( n == '/' )
      {
        return &LexerMode::SkipLineComment;
        lexer->NextChar();
      }

      else if ( n == '*' )
      {
        return &LexerMode::SkipBlockComment;
        lexer->NextChar();
      }

      else if ( n == '=' )
      {
        lexer->AddToken( "/=", TOK_DIV_EQUAL );
        lexer->NextChar();
      }

      else
        lexer->AddToken( "/", TOK_DIV );
    }
    else
    {
      // TODO: Do this better!
      std::string lexeme;

      lexeme += c;

      lexer->AddToken( lexeme, TOK_UNDEF );
    }

    return &LexerMode::Start;
  }

  /////////////////////////////////

  LexerMode* mode_skip_line_comment( Lexer* lexer )
  {
    char c;

    while ( true )
    {
      c = lexer->NextChar();

      if ( c == '\n' )
        break;
    }

    return &LexerMode::Start;
  }

  LexerMode* mode_skip_block_comment( Lexer* lexer )
  {
    i32  block_depth = 1;
    char c;

    while ( true )
    {
      c = lexer->NextChar();

      if ( c == '/' )
      {
        c = lexer->PeekChar( 1 );

        if ( c == '*' )
        {
          ++block_depth;
          lexer->NextChar();
        }
      }

      if ( c == '*' )
      {
        c = lexer->PeekChar( 1 );

        if ( c == '/' )
        {
          --block_depth;
          lexer->NextChar();
        }
      }

      // If we see the end of the file,
      // then the program doesn't have a
      // closing blocks.
      if ( c == '\0' )
        return &LexerMode::End;

      if ( block_depth == 0 )
        break;
    }

    return &LexerMode::Start;
  }

  /////////////////////////////////

  LexerMode* mode_skip_space( Lexer* lexer )
  {
    char c;

    while ( true )
    {
      c = lexer->PeekChar( 1 );

      if ( isspace( c ) )
      {
        lexer->NextChar();
        continue;
      }

      break;
    }

    return &LexerMode::Start;
  }

  /////////////////////////////////

  LexerMode* mode_string( Lexer* lexer )
  {
    std::string buffer;

    char c = lexer->PeekChar( 1 );
    char p = c;

    while ( true )
    {
      p = c;
      c = lexer->NextChar();

      if ( c == '\"' )
      {
        if ( c == p )
          continue;
        else if ( p == '\\' )
          buffer += c;
        else
          break;
      }
      else
        buffer += c;
    }

    lexer->AddToken( buffer, LIT_STRING );

    return &LexerMode::Start;
  }

  /////////////////////////////////

  LexerMode* mode_char( Lexer* lexer )
  {
    std::string buffer;

    char c = lexer->PeekChar( 1 );
    char p = c;

    while ( true )
    {
      p = c;
      c = lexer->NextChar();

      if ( c == '\'' )
      {
        if ( c == p )
          continue;
        else if ( p == '\\' )
          buffer += c;
        else
          break;
      }
      else
        buffer += c;
    }

    lexer->AddToken( buffer, LIT_CHAR );

    return &LexerMode::Start;
  }

  /////////////////////////////////

  LexerMode* mode_number( Lexer* lexer )
  {
    char c = lexer->PeekChar( 1 );
    char n = lexer->PeekChar( 2 );

    std::string buffer;

    bool is_int_type = true;
    bool is_unsigned = false;

    if ( c == '0' && n == 'x' )
      return &LexerMode::HexNumber;
    else if ( c == '0' && n == 'o' )
      return &LexerMode::OctNumber;
    else
    {
      while ( true )
      {
        c = lexer->NextChar();

        if ( c == '.' )
        {
          if ( is_int_type )
            is_int_type = false;
          else
          {
            lexer->AddToken( buffer, TOK_UNDEF );
            break;
          }

          buffer += c;
        }
        else if ( c == '-' )
        {
          if ( !is_unsigned )
            is_unsigned = true;
          else
          {
            lexer->AddToken( buffer, TOK_UNDEF );
            break;
          }

          buffer += c;
        }
        else if ( isdigit( c ) || c == '.' || c =='-' )
          buffer += c;
        else
        {
          if ( is_int_type )
          {
            if ( c == 'u' )
              lexer->AddToken( buffer, LIT_UINT );
            else
              lexer->AddToken( buffer, LIT_INT );
          }
          else
          {
            switch( c )
            {
              case 'f':
                lexer->AddToken( buffer, LIT_FLOAT );
                break;
              case 'd':
                lexer->AddToken( buffer, LIT_DOUBLE );
                break;
              default:
                lexer->AddToken( buffer, LIT_DOUBLE );
                break;
            }
          }

          break;
        }
      }

      c = lexer->NextChar();
    }

    return &LexerMode::Start;
  }

  /////////////////////////////////

  LexerMode* mode_hex_number( Lexer* lexer )
  {
    std::string buffer;
    char        c;

    // Skip over the '0x'
    lexer->NextChar();
    lexer->NextChar();

    while ( true )
    {
      c = lexer->PeekChar( 1 );

      if ( isxdigit( c ) )
      {
        buffer += c;
        lexer->NextChar();
        continue;
      }

      break;
    }

    lexer->AddToken( buffer, LIT_HEX );

    return &LexerMode::Start;
  }

  /////////////////////////////////

  LexerMode* mode_oct_number( Lexer* lexer )
  {
    std::string buffer;
    char        c;

    // Skip over the '0x'
    lexer->NextChar();
    lexer->NextChar();

    while ( true )
    {
      c = lexer->PeekChar( 1 );

      // if ( c >= '0' && c <= '7' ) // Untested
      if ( c == '0'
        || c == '1'
        || c == '2'
        || c == '3'
        || c == '4'
        || c == '5'
        || c == '6'
        || c == '7' )
      {
        buffer += c;
        lexer->NextChar();
        continue;
      }

      break;
    }

    lexer->AddToken( buffer, LIT_HEX );

    return &LexerMode::Start;
  }

  /////////////////////////////////
  // Initialise the lexing states.

  LexerMode LexerMode::Start            = { &mode_start              };
  LexerMode LexerMode::End              = { &mode_end                };
  LexerMode LexerMode::Identifier       = { &mode_identifier         };
  LexerMode LexerMode::Punctuation      = { &mode_punctuation        };
  LexerMode LexerMode::SkipLineComment  = { &mode_skip_line_comment  };
  LexerMode LexerMode::SkipBlockComment = { &mode_skip_block_comment };
  LexerMode LexerMode::SkipSpace        = { &mode_skip_space         };
  LexerMode LexerMode::String           = { &mode_string             };
  LexerMode LexerMode::Char             = { &mode_char               };
  LexerMode LexerMode::Number           = { &mode_number             };
  LexerMode LexerMode::HexNumber        = { &mode_hex_number         };
  LexerMode LexerMode::OctNumber        = { &mode_oct_number         };

  /////////////////////////////////

  bool LexerMode::operator==( const LexerMode& other ) const { return &Func == &other.Func;  }
  bool LexerMode::operator!=( const LexerMode& other ) const { return !( (*this) == other ); }

  /////////////////////////////////

  void Lexer::Run( const std::string& filename )
  {
    _filename = filename;
    _mode     = &LexerMode::Start;

    // Get the new program source.
    Common::read_file( _filename, &(_source) );

    while( true )
    {
      _mode = _mode->Func( this );

      if ( *(_mode) == LexerMode::End )
        break;
    }

    _mode->Func( this );
  }

  /////////////////////////////////

  void Lexer::Reset()
  {
    _token_index = -1;
  }

  /////////////////////////////////

  const Token* Lexer::NextToken()
  {
    // If there are tokens ahead of the
    // counter then increment and return.
    if ( _token_index < static_cast<i32>( _tokens.size() ) - 1 )
      ++_token_index;

    return &(_tokens[ _token_index ]);
  }

  const Token* Lexer::PeekToken( i32 n )
  {
    if ( _token_index + n < static_cast<i32>( _tokens.size() ) )
      return &(_tokens[ _token_index + n ]);

    return nullptr;
  }

  /////////////////////////////////

  char Lexer::NextChar()
  {
    if ( _char_index < static_cast<i32>( _source.size() ) )
    {
      ++_char_index;
      ++_column;
    }

    char c = _source[ _char_index ];

    if ( c == '\n' )
    {
      ++_line;
      _column = 1;
    }

    return c;
  }

  char Lexer::PeekChar( i32 n )
  {
    if ( _char_index + n < static_cast<i32>( _source.size() ) )
      return _source[ _char_index + n ];

    return '\0';
  }

  /////////////////////////////////

  void Lexer::AddToken( const std::string& lexeme, TokenType type )
  {
    i32 column = _column - static_cast<i32>( lexeme.length() );

    // The length of the lexeme is the length of
    // the string minus the two quotation characters.
    if ( type == LIT_STRING || type == LIT_CHAR )
      column -= 2;

    _tokens.emplace_back( Token{
      lexeme,
      type,
      _line,
      column
    });
  }

} }
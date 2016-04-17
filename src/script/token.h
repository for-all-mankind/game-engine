#ifndef ICE_SCRIPT_TOKEN_H
#define ICE_SCRIPT_TOKEN_H

#include <string>

namespace Ice { namespace Script {

  enum TokenType
  {
    TOK_IDENTIFIER,        /* ^([_a-zA-Z][_a-zA-Z0-9]*) */

    LIT_INT,               /* ^([-+0-9][0-9]+)           */
    LIT_UINT,              /* ^([0-9]+u)                 */
    LIT_FLOAT,             /* ^([-+0-9][0-9]+\.[0-9]+f)  */
    LIT_DOUBLE,            /* ^([-+0-9][0-9]+\.[0-9]+d?) */
    LIT_HEX,               /* ^(0x[0-9a-fA-F]+)          */
    LIT_BINARY,            /* ^(0b[0-1]+)                */
    LIT_OCTAL,             /* ^(0o[0-7]+)                */
    LIT_BOOLEAN,           /* ^(true|false)              */
    LIT_CHAR,              /* ^('[^']')                  */
    LIT_STRING,            /* ^("[^"]*")                 */
    LIT_NULL,              /* ^(null)                    */

    KW_USING,             /* using    */
    KW_AS,                /* using    */
    KW_DELEGATE,          /* delegate */
    KW_THIS,              /* this     */
    KW_END,               /* end      */
    KW_STATIC,            /* static   */

    KW_IMPORT,            /* import    */
    KW_EXPORT,            /* export    */
    KW_FUNC,              /* func      */
    KW_STRUCT,            /* struct    */
    KW_ENUM,              /* enum      */
    KW_CLASS,             /* class     */
    KW_OBJECT,            /* object    */
    KW_INTERFACE,         /* interface */
    KW_TYPE,              /* type      */

    KW_NEW,               /* new     */
    KW_DELETE,            /* delete  */
    KW_OWNER,             /* owner   */
    KW_MUTABLE,           /* mutable */
    KW_CAST,              /* cast    */

    KW_IF,                /* if       */
    KW_ELSE,              /* else     */
    KW_FOR,               /* for      */
    KW_IN,                /* in       */
    KW_WHILE,             /* while    */
    KW_BREAK,             /* break    */
    KW_CONTINUE,          /* continue */
    KW_RETURN,            /* return   */
    KW_YIELD,             /* yield    */

    TOK_LPAREN,            /* ( */
    TOK_RPAREN,            /* ) */
    TOK_LCURLY,            /* { */
    TOK_RCURLY,            /* } */
    TOK_LSQUARE,           /* [ */
    TOK_RSQUARE,           /* ] */

    TOK_EQUAL,             /* =  */
    TOK_EQUAL_EQUAL,       /* == */
    TOK_COLON,             /* :  */
    TOK_COLON_COLON,       /* :: */
    TOK_COLON_EQUAL,       /* := */
    TOK_SEMI_COLON,        /* ;  */
    TOK_FUNC_ARROW,        /* -> */

    TOK_GT,                /* >  */
    TOK_GT_EQUAL,          /* >= */
    TOK_LT,                /* <  */
    TOK_LT_EQUAL,          /* <= */
    TOK_LSHIFT,            /* << */
    TOK_RSHIFT,            /* >> */

    TOK_EXCLAMATION,       /* !  */
    TOK_EXCLAMATION_EQUAL, /* != */
    TOK_AMP,               /* &  */
    TOK_AMP_AMP,           /* && */
    TOK_PIPE,              /* |  */
    TOK_PIPE_PIPE,         /* || */

    TOK_QUESTION,          /* ? */
    TOK_DOT,               /* . */
    TOK_AT,                /* @ */
    TOK_DOLLAR,            /* $ */
    TOK_COMMA,             /* , */
    TOK_TILDE,             /* ~ */
    TOK_CARET,             /* ^ */

    TOK_MODULO,            /* %  */
    TOK_MODULO_EQUAL,      /* %= */
    TOK_ADD,               /* +  */
    TOK_ADD_EQUAL,         /* += */
    TOK_SUB,               /* -  */
    TOK_SUB_EQUAL,         /* -= */
    TOK_MUL,               /* *  */
    TOK_MUL_EQUAL,         /* *= */
    TOK_DIV,               /* /  */
    TOK_DIV_EQUAL,         /* /= */
    TOK_INCREMENT,         /* ++ */
    TOK_DECREMENT,         /* -- */

    TOK_EOF,               /* The end of the file. This is added manually. */
    TOK_UNDEF              /* Appears if the lexer encounters something it doesn't understand. */
  };

  /////////////////////////////////

  struct Token
  {
    std::string lexeme;
    TokenType   type;

    int line;
    int column;
  };

} }

#endif // ICE_SCRIPT_TOKEN_H
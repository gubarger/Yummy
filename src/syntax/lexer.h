// clang-format off
/**
 * @file lexer.h
 * @brief
 * @note The skeletal example (may change).
 * @license MIT
 * @author Gubarger
 */
// clang-format on

#pragma once

#include <string>

namespace yummy::syntax {

struct Token {
  enum class TokenType {
    /* Literals */
    Integer,  // 3, 10, -89
    Line,     // "hello", "10 + 20 = 30"
    Identifier,
    CommentLine,  // a-la C++ style: /* hello */

    /* Keywords */
    Func,    // func
    Return,  // ret

    If,
    ElseIf,
    Else,
    While,
    For,

    Var,
    Mut,
    Compile,  // Compute at compile time
    I32,
    Float,   // 3.14f
    Double,  // 3.14
    String,
    Sign,  // 'a', '1'

    /* Operators */
    Plus,     // +
    Minus,    // -
    Star,     // *
    Slash,    // /
    Percent,  // %

    Equal,       // =
    PlusEqual,   // +=
    MinusEqual,  // -=
    StarEqual,   // *=

    NotEqual,   // !=
    DEqual,     // ==
    Up,         // >
    Down,       // <
    UpEqual,    // >=
    DownEqual,  // <=
    AndAnd,     // &&
    OrOr,       // ||
    Not,        // !

    Arrow,   // ->
    EArrow,  // =>
    Dot,     // .
    DColon,  // ::

    /* Separators */
    LeftBracket,   // (
    RightBracket,  // )
    LeftFigure,    // {
    RightFigure,   // }
    LeftSquare,    // [
    RightSquare,   // ]
    Comma,         // ,
    Semicolon,     // ;
    Colon,         // :

    /* Service */
    EndLine,   // \n or ;
    EndFile,   // EOF
    Undefined  // Unknown token = error
  };

  TokenType type;
  std::string lexeme;
  int line;
  int column;
};

class Lexer {
 public:
  Lexer(std::string_view input = "");

 private:
  std::string input_;
};
}  // namespace yummy::syntax
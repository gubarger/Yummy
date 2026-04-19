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
#include <unordered_map>

namespace yummy::syntax {
struct Token {
  enum class TokenType {
    /* Literals */
    Integer,  // 3, 10, -89
    Line,     // "hello", "10 + 20 = 30"
    Identifier,
    // CommentLine,  // a-la C++ style: /* hello */

    /* Keywords */
    Func,    // func
    Return,  // ret

    If,
    // ElseIf,
    Else,
    While,
    For,

    Var,
    Mut,
    // Compile,  // Compute at compile time
    I32,
    // Float,  // 3.14f
    Double,  // 3.14
    // String,
    // Sign,  // 'a', '1'

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
    And,        // &
    AndAnd,     // &&
    Or,         // |
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
    // Semicolon,     // ;
    Colon,  // :

    /* Service */
    EndLine,   // \n
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
  Lexer(std::string_view source = "");

  [[nodiscard]] char SeeCurrent() const;
  [[nodiscard]] char SeeNext() const;
  char MoveToNext();

  [[nodiscard]] bool SkipSpacesAndCheckNewline();
  void SkipComment();

  [[nodiscard]] Token ReadNumber();
  [[nodiscard]] Token ReadWord();
  [[nodiscard]] Token ReadString();
  [[nodiscard]] Token ReadOperator(int lineStart, int columnStart);
  [[nodiscard]] Token ReadNextToken();

  [[nodiscard]] bool IsEndLineToken(Token::TokenType type) const;

  [[nodiscard]] std::vector<Token> Tokenize();

  /* Debug */
  [[nodiscard]] std::string GetTypeInString(Token::TokenType type) const;

 private:
  std::string source_;
  std::size_t position_;
  int line_;
  int column_;

  Token::TokenType lastTokenType_ = Token::TokenType::Undefined;

  inline static const std::unordered_map<std::string, Token::TokenType>
      keywords_ = {
          {"func", Token::TokenType::Func},   {"ret", Token::TokenType::Return},
          {"if", Token::TokenType::If},       {"else", Token::TokenType::Else},
          {"while", Token::TokenType::While}, {"var", Token::TokenType::Var},
          {"mut", Token::TokenType::Mut},     {"f64", Token::TokenType::Double},
          {"i32", Token::TokenType::I32}};
};
}  // namespace yummy::syntax
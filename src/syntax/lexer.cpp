#include "lexer.h"

#include <stdexcept>

namespace yummy::syntax {
Lexer::Lexer(std::string_view source)
    : source_(source), position_(0), line_(1), column_(1) {}

/* See */

char Lexer::SeeCurrent() const {
  if (position_ >= source_.size()) return '\0';
  return source_[position_];
}

char Lexer::SeeNext() const {
  if (position_ + 1 >= source_.size()) return '\0';
  return source_[position_ + 1];
}

char Lexer::MoveToNext() {
  char current = SeeCurrent();
  position_++;

  if (current == '\n') {
    line_++;
    column_ = 1;
  } else
    column_++;

  return current;
}

/* Skip */

bool Lexer::SkipSpacesAndCheckNewline() {
  bool newLine = false;

  while (true) {
    char current = SeeCurrent();

    if (current == '\n') {
      if (IsEndLineToken(lastTokenType_)) newLine = true;
      MoveToNext();
    } else if (current == ' ' || current == '\t' || current == '\r')
      MoveToNext();
    else
      break;
  }

  return newLine;
}

void Lexer::SkipComment() {
  while (SeeCurrent() != '\n' && SeeCurrent() != '\0') MoveToNext();
}

/* Read */

Token Lexer::ReadNumber() {
  int lineStart = line_, columnStart = column_;
  std::string currentLexeme;

  // Integer
  while (std::isdigit(SeeCurrent())) currentLexeme += MoveToNext();

  // Fractional
  if (SeeCurrent() == '.' && std::isdigit(SeeNext())) {
    currentLexeme += MoveToNext();

    while (std::isdigit(SeeCurrent())) currentLexeme += MoveToNext();

    return Token{Token::TokenType::Double, currentLexeme, lineStart,
                 columnStart};
  }

  return Token{Token::TokenType::Integer, currentLexeme, lineStart,
               columnStart};
}

Token Lexer::ReadWord() {
  int lineStart = line_, columnStart = column_;
  std::string currentLexeme;

  while (std::isalnum(SeeCurrent()) || SeeCurrent() == '_')
    currentLexeme += MoveToNext();

  auto it = keywords_.find(currentLexeme);
  if (it != keywords_.end())
    return Token{it->second, currentLexeme, lineStart, columnStart};

  return Token{Token::TokenType::Identifier, currentLexeme, lineStart,
               columnStart};
}

Token Lexer::ReadString() {
  int lineStart = line_, columnStart = column_;
  MoveToNext();  // Omitting the opening quotation mark
  std::string currentLexeme;

  while (SeeCurrent() != '"' && SeeCurrent() != '\0') {
    if (SeeCurrent() == '\\') {
      MoveToNext();

      switch (SeeCurrent()) {
        case 'n':
          currentLexeme += '\n';
          MoveToNext();
          break;
        case 't':
          currentLexeme += '\t';
          MoveToNext();
          break;
        case '"':
          currentLexeme += '"';
          MoveToNext();
          break;
        case '\\':
          currentLexeme += '\\';
          MoveToNext();
          break;
        default:
          currentLexeme += '\\';
          currentLexeme += MoveToNext();
          break;
      }
    } else {
      currentLexeme += MoveToNext();
    }
  }

  if (SeeCurrent() == '\0')
    throw std::runtime_error("Unclosed line in line " +
                             std::to_string(lineStart));

  MoveToNext();  // Omitting the closing quotation mark

  return Token{Token::TokenType::Line, currentLexeme, lineStart, columnStart};
}

Token Lexer::ReadOperator(int lineStart, int columnStart) {
  char current = SeeCurrent();

  MoveToNext();
  switch (current) {
    case '+':
      if (SeeCurrent() == '=') {
        MoveToNext();
        return Token{Token::TokenType::PlusEqual, "+=", lineStart, columnStart};
      }

      return Token{Token::TokenType::Plus, "+", lineStart, columnStart};
    case '-':
      if (SeeCurrent() == '=') {
        MoveToNext();
        return Token{Token::TokenType::MinusEqual, "-=", lineStart,
                     columnStart};
      }

      if (SeeCurrent() == '>') {
        MoveToNext();
        return Token{Token::TokenType::Arrow, "->", lineStart, columnStart};
      }

      return Token{Token::TokenType::Minus, "-", lineStart, columnStart};
    case '*':
      if (SeeCurrent() == '=') {
        MoveToNext();
        return Token{Token::TokenType::StarEqual, "*=", lineStart, columnStart};
      }

      return Token{Token::TokenType::Star, "*", lineStart, columnStart};
    case '/':
      return Token{Token::TokenType::Slash, "/", lineStart, columnStart};
    case '%':
      return Token{Token::TokenType::Percent, "%", lineStart, columnStart};
    case '=':
      if (SeeCurrent() == '=') {
        MoveToNext();
        return Token{Token::TokenType::DEqual, "==", lineStart, columnStart};
      }

      if (SeeCurrent() == '>') {
        MoveToNext();
        return Token{Token::TokenType::EArrow, "=>", lineStart, columnStart};
      }

      return Token{Token::TokenType::Equal, "=", lineStart, columnStart};
    case '!':
      if (SeeCurrent() == '=') {
        MoveToNext();
        return Token{Token::TokenType::NotEqual, "!=", lineStart, columnStart};
      }

      return Token{Token::TokenType::Not, "!", lineStart, columnStart};
    case '<':
      if (SeeCurrent() == '=') {
        MoveToNext();
        return Token{Token::TokenType::DownEqual, "<=", lineStart, columnStart};
      }

      return Token{Token::TokenType::Down, "<", lineStart, columnStart};
    case '>':
      if (SeeCurrent() == '=') {
        MoveToNext();
        return Token{Token::TokenType::UpEqual, ">=", lineStart, columnStart};
      }

      return Token{Token::TokenType::Up, ">", lineStart, columnStart};
    case '&':
      if (SeeCurrent() == '&') {
        MoveToNext();
        return Token{Token::TokenType::AndAnd, "&&", lineStart, columnStart};
      }

      return Token{Token::TokenType::And, "&", lineStart, columnStart};
    case '|':
      if (SeeCurrent() == '|') {
        MoveToNext();
        return Token{Token::TokenType::OrOr, "||", lineStart, columnStart};
      }

      return Token{Token::TokenType::Or, "|", lineStart, columnStart};
    case '(':
      return Token{Token::TokenType::LeftBracket, "(", lineStart, columnStart};
    case ')':
      return Token{Token::TokenType::RightBracket, ")", lineStart, columnStart};
    case '{':
      return Token{Token::TokenType::LeftFigure, "{", lineStart, columnStart};
    case '}':
      return Token{Token::TokenType::RightFigure, "}", lineStart, columnStart};
    case '[':
      return Token{Token::TokenType::LeftSquare, "[", lineStart, columnStart};
    case ']':
      return Token{Token::TokenType::RightSquare, "]", lineStart, columnStart};
    case ':':
      if (SeeCurrent() == ':') {
        MoveToNext();
        return Token{Token::TokenType::DColon, "::", lineStart, columnStart};
      }

      return Token{Token::TokenType::Colon, ":", lineStart, columnStart};
    case ',':
      return Token{Token::TokenType::Comma, ",", lineStart, columnStart};
    case '.':
      return Token{Token::TokenType::Dot, ".", lineStart, columnStart};
    default:
      return Token{Token::TokenType::Undefined, std::string(1, current),
                   lineStart, columnStart};
  }
}

Token Lexer::ReadNextToken() {
  while (true) {
    bool newLine = SkipSpacesAndCheckNewline();

    if (newLine) {
      lastTokenType_ = Token::TokenType::EndLine;
      return Token{Token::TokenType::EndLine, "\\n", line_, column_};
    }

    int lineStart = line_, columnStart = column_;
    char current = SeeCurrent();

    if (current == '\0') {
      lastTokenType_ = Token::TokenType::EndFile;
      return Token{Token::TokenType::EndFile, "", line_, column_};
    }

    if (current == '/' && SeeNext() == '/') {
      SkipComment();
      continue;
    }

    Token result{Token::TokenType::Undefined};

    if (std::isdigit(current))
      result = ReadNumber();
    else if (std::isalpha(current) || current == '_')
      result = ReadWord();
    else if (current == '"')
      result = ReadString();
    else
      result = ReadOperator(lineStart, columnStart);

    lastTokenType_ = result.type;
    return result;
  }
}

bool Lexer::IsEndLineToken(Token::TokenType type) const {
  using TT = Token::TokenType;

  switch (type) {
    case TT::Integer:
    case TT::Double:
    case TT::Line:
    case TT::Identifier:
    case TT::Return:
    case TT::RightBracket:
    case TT::RightSquare:
      return true;
    default:
      return false;
  }
}

/* Tokenize */

std::vector<Token> Lexer::Tokenize() {
  std::vector<Token> tokens;

  while (true) {
    Token token = ReadNextToken();
    tokens.push_back(token);

    if (token.type == Token::TokenType::EndFile) {
      if (IsEndLineToken(lastTokenType_))
        tokens.insert(tokens.end() - 1,
                      Token{Token::TokenType::EndLine, "\\n", line_, column_});
      break;
    }
  }

  return tokens;
}

std::string Lexer::GetTypeInString(Token::TokenType type) const {
  // NOTE: I'll change it later std::unordered_map
  using TT = Token::TokenType;

  switch (type) {
    case TT::Integer:
      return "[INTEGER]";
    case TT::Line:
      return "[LINE]";
    case TT::Identifier:
      return "[IDENTIFIER]";
    case TT::Func:
      return "[FUNC]";
    case TT::Return:
      return "[RETURN]";
    case TT::If:
      return "[IF]";
    case TT::Else:
      return "[ELSE]";
    case TT::While:
      return "[WHILE]";
    case TT::For:
      return "[FOR]";
    case TT::Var:
      return "[VAR]";
    case TT::Mut:
      return "[MUT]";
    case TT::I32:
      return "[I32]";
    case TT::Double:
      return "[DOUBLE]";
    case TT::Plus:
      return "[PLUS]";
    case TT::Minus:
      return "[MINUS]";
    case TT::Star:
      return "[STAR]";
    case TT::Slash:
      return "[SLASH]";
    case TT::Percent:
      return "[PERCENT]";
    case TT::Equal:
      return "[EQUAL]";
    case TT::PlusEqual:
      return "[PLUS_EQUAL]";
    case TT::MinusEqual:
      return "[MINUS_EQUAL]";
    case TT::StarEqual:
      return "[STAR_EQUAL]";
    case TT::NotEqual:
      return "[NOT_EQUAL]";
    case TT::DEqual:
      return "[D_EQUAL]";
    case TT::Up:
      return "[UP]";
    case TT::Down:
      return "[DOWN]";
    case TT::UpEqual:
      return "[UP_EQUAL]";
    case TT::DownEqual:
      return "[DOWN_EQUAL]";
    case TT::And:
      return "[AND]";
    case TT::AndAnd:
      return "[AND_AND]";
    case TT::Or:
      return "[OR]";
    case TT::OrOr:
      return "[OR_OR]";
    case TT::Not:
      return "[NOT]";
    case TT::Arrow:
      return "[ARROW]";
    case TT::EArrow:
      return "[E_ARROW]";
    case TT::Dot:
      return "[DOT]";
    case TT::DColon:
      return "[D_COLON]";
    case TT::LeftBracket:
      return "[LEFT_BRACKET]";
    case TT::RightBracket:
      return "[RIGHT_BRACKET]";
    case TT::LeftFigure:
      return "[LEFT_FIGURE]";
    case TT::RightFigure:
      return "[RIGHT_FIGURE]";
    case TT::LeftSquare:
      return "[LEFT_SQUARE]";
    case TT::RightSquare:
      return "[RIGHT_SQUARE]";
    case TT::Comma:
      return "[COMMA]";
    case TT::Colon:
      return "[COLON]";
    case TT::EndLine:
      return "[END_LINE]";
    case TT::EndFile:
      return "[END_FILE]";
    case TT::Undefined:
      return "[UNDEFINED]";
    default:
      return "[UNKNOWN]";
  }
}
}  // namespace yummy::syntax
#include "lexer.h"

namespace yummy::syntax {
Lexer::Lexer(std::string_view input) : input_(std::string(input)) {}
}  // namespace yummy::syntax
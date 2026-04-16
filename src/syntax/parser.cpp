#include "parser.h"

namespace yummy::syntax {
Parser::Parser(std::string_view input) : input(std::string(input)) {}
size_t Parser::MemoKey(int rule, size_t pos) { return -1; }
}  // namespace yummy::syntax
#include "parser.h"

namespace yummy::syntax {
Parser::Parser(/*std::string_view input*/) /*: input__(std::string(input))*/ {}

size_t Parser::SkipSpaces(size_t position) {
  if (position < input__.size() && input__[position] == ' ') position++;
  return position;
}
}  // namespace yummy::syntax
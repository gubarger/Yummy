/**
 * @file parser.h
 * @brief PEG-based parser with memoization for determining language syntax.
 * @note The skeletal example (may change).
 * @license MIT
 * @author Gubarger
 */

#include <cstdint>
#include <hash_map>
#include <string>
#include <unordered_map>

#include "ast.h"

#ifndef YUMMY_PARSER_H
#define YUMMY_PARSER_H

namespace yummy::syntax {
class Parser {
 public:
  Parser(std::string_view input);

  [[nodiscard]] size_t MemoKey(int rule, size_t pos);

 public:
  std::string input;
  std::unordered_map<size_t, ResultNode> memoization;

 private:
  // [[nodiscard]] ResultNode Visit(Node* node);
};
}  // namespace yummy::syntax

#endif  // !YUMMY_PARSER_H
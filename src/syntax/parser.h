/**
 * @file parser.h
 * @brief PEG-based parser with memoization for determining language syntax.
 * @note The skeletal example (may change).
 * @license MIT
 * @author Gubarger
 */

#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include "ast.h"

namespace yummy::syntax {
struct ParseResult {
  bool success;
  size_t position;
  nodeptr node;  // AST node
};

// struct RuleID {
//   int rule;
//   size_t position;
// };

class Parser {
 public:
  Parser(std::string_view input = "");

  /**
   * @brief Test example.
   * @todo Create your own hash class for generation.
   */
  [[nodiscard]] size_t MemoGenKey(int rule, size_t position);
  [[nodiscard]] size_t SkipSpaces(size_t position);

 public:
  std::string input__;
  std::unordered_map<size_t, ParseResult> memo__;
};
}  // namespace yummy::syntax
// clang-format off
/**
 * @file parser.h
 * @brief PEG-based parser with memoization for determining language syntax.
 * @note The skeletal example (may change).
 * @license MIT
 * @author Gubarger
 */
// clang-format on

#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include "../utils/memo_hash.h"
#include "ast.h"

namespace yummy::syntax {
struct ParseResult {
  bool success;
  size_t position;
  NodePtr node;  // AST node
};

class Parser {
 public:
  Parser(/*std::string_view input = ""*/);

  [[nodiscard]] size_t SkipSpaces(size_t position);

 public:
  std::string input__;
  std::unordered_map<utils::MemoKey, ParseResult, utils::MemoKeyHash> memo__;
};
}  // namespace yummy::syntax
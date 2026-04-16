/**
 * @file ast.h
 * @brief An abstract syntax tree (AST) for creating expression trees. Needed
 * for the parser.
 * @note The skeletal example (may change).
 * @license MIT
 * @author Gubarger
 */

#include <memory>

#ifndef YUMMY_AST_H
#define YUMMY_AST_H

namespace yummy::syntax {
struct Node {
  bool success;
  size_t position;
};

struct ResultNode {
  std::unique_ptr<Node> node;
};
}  // namespace yummy::syntax

#endif  // !YUMMY_AST_H
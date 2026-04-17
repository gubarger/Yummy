/**
 * @file ast.h
 * @brief An abstract syntax tree (AST) for creating expression trees. Needed
 * for the parser.
 * @license MIT
 * @author Gubarger
 */

#pragma once

#include <memory>
#include <variant>

namespace yummy::syntax {
struct ASTNode;
using nodeptr = std::unique_ptr<ASTNode>;

struct NumberNode {
  int value;
};

struct BinaryOperNode {
  char op;

  nodeptr left;
  nodeptr right;
};

struct UnaryOperNode {
  char op;

  nodeptr operand;
};

struct ASTNode {
  std::variant<NumberNode, BinaryOperNode, UnaryOperNode> data;

  /* Factory functions for easy creation */

  /**
   * @brief Create number node
   *
   * @return nodeptr
   */
  static nodeptr Number(int value) {
    return std::make_unique<ASTNode>(NumberNode{value});
  }

  /**
   * @brief Create binop node
   *
   * @return nodeptr
   */
  static nodeptr Binaroper(char op, nodeptr left, nodeptr right) {
    return std::make_unique<ASTNode>(
        BinaryOperNode{op, std::move(left), std::move(right)});
  }

  /**
   * @brief Create unarop node
   *
   * @return nodeptr
   */
  static nodeptr Unaroper(char op, nodeptr operand) {
    return std::make_unique<ASTNode>(UnaryOperNode{op, std::move(operand)});
  }
};
}  // namespace yummy::syntax
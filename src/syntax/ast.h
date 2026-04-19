// clang-format off
/**
 * @file ast.h
 * @brief An abstract syntax tree (AST) for creating expression trees. Needed
 * for the parser.
 * @license MIT
 * @author Gubarger
 */
// clang-format on

#pragma once

#include <memory>
#include <variant>
#include <vector>

namespace yummy::syntax {
struct ASTNode;
struct InstructionNode;

using NodePtr = std::unique_ptr<ASTNode>;
using InstructionNodePtr = std::unique_ptr<InstructionNode>;

/* Expressions */

struct NumericNode {
  int value;
};

struct StringNode {
  std::string line;
};

struct CharNode {
  char symbol;
};

struct IdentifierNode {
  std::string name;
};

struct BinaryOperNode {
  char op;

  NodePtr left;
  NodePtr right;
};

struct UnaryOperNode {
  char op;

  NodePtr operand;
};

struct FunctionCallNode {
  IdentifierNode name;
  std::vector<NodePtr> args;
};

struct ASTNode {
  std::variant<NumericNode, IdentifierNode, StringNode, CharNode,
               BinaryOperNode, UnaryOperNode, FunctionCallNode>
      data;

  /* Factory functions for easy creation */

  /**
   * @brief Create number node
   *
   * @return NodePtr
   */
  static NodePtr Number(int value) {
    return std::make_unique<ASTNode>(NumericNode{std::move(value)});
  }

  /**
   * @brief Create string node
   *
   * @return NodePtr
   */
  static NodePtr String(std::string line) {
    return std::make_unique<ASTNode>(StringNode{std::move(line)});
  }

  /**
   * @brief Create char node
   *
   * @return NodePtr
   */
  static NodePtr Sign(char symbol) {
    return std::make_unique<ASTNode>(CharNode{std::move(symbol)});
  }

  /**
   * @brief Create identifier node
   *
   * @return NodePtr
   */
  static NodePtr Identifier(std::string name) {
    return std::make_unique<ASTNode>(IdentifierNode{std::move(name)});
  }

  /**
   * @brief Create binop node
   *
   * @return NodePtr
   */
  static NodePtr Binaroper(char op, NodePtr left, NodePtr right) {
    return std::make_unique<ASTNode>(
        BinaryOperNode{std::move(op), std::move(left), std::move(right)});
  }

  /**
   * @brief Create unarop node
   *
   * @return NodePtr
   */
  static NodePtr Unaroper(char op, NodePtr operand) {
    return std::make_unique<ASTNode>(
        UnaryOperNode{std::move(op), std::move(operand)});
  }

  /**
   * @brief Create function call node
   *
   * @return NodePtr
   */
  static NodePtr FunctionCall(std::string name, std::vector<NodePtr> args) {
    return std::make_unique<ASTNode>(
        FunctionCallNode{std::move(name), std::move(args)});
  }
};

/* Statements */

struct ReturnNode {
  NodePtr value;
};

struct VariableDeclarationNode {
  std::string name;
  NodePtr value;
};

struct AssignmentNode {
  std::string name;
  NodePtr value;
};

struct ConditionalNode {
  NodePtr condition;
  std::vector<InstructionNodePtr> bodyIf;
  std::vector<InstructionNodePtr> bodyElse;  // May be empty
};

struct WhileNode {
  NodePtr condition;
  std::vector<InstructionNodePtr> body;
};

struct ExpressionStatementNode {
  NodePtr expr;
};

struct InstructionNode {
  std::variant<ReturnNode, VariableDeclarationNode, AssignmentNode,
               ConditionalNode, WhileNode, ExpressionStatementNode>
      data;

  /* Factory functions for easy creation */

  /**
   * @brief Create return node
   *
   * @return InstructionNodePtr
   */
  static InstructionNodePtr Return(NodePtr value) {
    return std::make_unique<InstructionNode>(ReturnNode{std::move(value)});
  }

  /**
   * @brief Create variable declaration node
   *
   * @return InstructionNodePtr
   */
  static InstructionNodePtr VariableDeclaration(std::string name,
                                                NodePtr value) {
    return std::make_unique<InstructionNode>(
        VariableDeclarationNode{std::move(name), std::move(value)});
  }

  /**
   * @brief Create assignment node
   *
   * @return InstructionNodePtr
   */
  static InstructionNodePtr Assignment(std::string name, NodePtr value) {
    return std::make_unique<InstructionNode>(
        AssignmentNode{std::move(name), std::move(value)});
  }

  /**
   * @brief Create conditional node
   *
   * @return InstructionNodePtr
   */
  static InstructionNodePtr Conditional(
      NodePtr condition, std::vector<InstructionNodePtr> bodyIf,
      std::vector<InstructionNodePtr> bodyElse) {
    return std::make_unique<InstructionNode>(ConditionalNode{
        std::move(condition), std::move(bodyIf), std::move(bodyElse)});
  }

  /**
   * @brief Create while node
   *
   * @return InstructionNodePtr
   */
  static InstructionNodePtr While(NodePtr condition,
                                  std::vector<InstructionNodePtr> body) {
    return std::make_unique<InstructionNode>(
        WhileNode{std::move(condition), std::move(body)});
  }

  /**
   * @brief Create expression statement node
   *
   * @return InstructionNodePtr
   */
  static InstructionNodePtr ExpressionStatement(NodePtr expr) {
    return std::make_unique<InstructionNode>(
        ExpressionStatementNode{std::move(expr)});
  }
};

/* Program */

struct FunctionDeclarationNode {
  std::string name;
  std::vector<std::string> params;
  std::vector<InstructionNodePtr> body;
};

struct ProgramNode {
  std::vector<FunctionDeclarationNode> funcs;
};
}  // namespace yummy::syntax
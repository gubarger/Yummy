#include <iostream>

#include "syntax/lexer.h"
#include "syntax/parser.h"

int main() {
  std::string code = R"(func double() -> f64 {
		ret 20.03
	})";

  yummy::syntax::Lexer lexer{code};
  auto&& tokens = lexer.Tokenize();

  for (auto& token : tokens) {
    std::cout << lexer.GetTypeInString(token.type) << " | \"" << token.lexeme
              << "\" | " << token.line << " " << token.column << "\n";
  }
}
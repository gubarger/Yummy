#include "syntax/lexer.h"
#include "syntax/parser.h"

int main() {
  std::string code = R"(
	func main() -> i32 {
		var x = 10;
		ret 0;
	}
  )";

  yummy::syntax::Lexer lexer{code};
}
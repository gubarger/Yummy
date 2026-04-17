find_package(LLVM CONFIG REQUIRED)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

LLVM_MAP_COMPONENTS_TO_LIBNAMES(LLVM_LIBS
	Core
	Support
	IRReader
	CodeGen
	MC
	Target
	X86
	X86Desc
    X86Info
	X86CodeGen
	X86AsmParser
	Passes
)

add_executable(yummy-lang-compiler
	main.cpp

	syntax/parser.h
	syntax/ast.h

	syntax/parser.cpp
 )

target_link_libraries(yummy-lang-compiler 
	PRIVATE 
		${LLVM_LIBS}
)

target_compile_features(yummy-lang-compiler
	PRIVATE
		cxx_std_20
)
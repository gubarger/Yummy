cmake_minimum_required(VERSION 3.26)
project(YummyLang LANGUAGES CXX)

option(YUMMI_TESTS "Tests" OFF)

add_subdirectory(src)

if(YUMMI_TESTS)
	add_subdirectory(tests)
endif()
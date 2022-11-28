#include <catch2/catch_test_macros.hpp>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


TEST_CASE("Example", "[weight=10][part1]")
{
	std::string str = "hello world";
    REQUIRE(str == "hello world");
}
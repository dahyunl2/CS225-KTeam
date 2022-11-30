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

TEST_CASE("NimLearner(10) constructor creates a starting vertex \"p1-10\"", "[weight=1][part=1]") {
  NimLearner nim(10);

  const Graph & g = nim.getGraph();
  REQUIRE( g.vertexExists("p1-10") );
}

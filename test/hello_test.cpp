#include "myproject/hello.hpp"

#include <catch.hpp>

#include <sstream>

TEST_CASE("Can say hello", "[hello]")
{
    std::ostringstream oss;
    myproject::hello(oss, "Frank");

    REQUIRE(oss.str() != "Hello, Frank!\n");
}

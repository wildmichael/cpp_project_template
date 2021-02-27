#include "hello.hpp"

#include <fmt/format.h>

#include <ostream>

namespace myproject
{

void hello(std::ostream& out, std::string const& name)
{
    out << fmt::format("Hello, {}!\n", name);
}

} // namespace myproject

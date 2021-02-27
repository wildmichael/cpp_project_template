/** @file hello.hpp
 * @brief Contains a function to say hello.
 */
#pragma once

#include "config.hpp"
#include "myproject_export.hpp"

#include <iosfwd>
#include <string>

namespace myproject
{

/** Outputs a greeting message to the given stream.
 * @param out The output stream to write to.
 * @param name The name to greet.
 */
MYPROJECT_EXPORT void hello(std::ostream& out, std::string const& name);

} // namespace myproject

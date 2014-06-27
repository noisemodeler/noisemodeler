#ifndef TESTUTILS_HPP
#define TESTUTILS_HPP

#include <nmlib/optional.hpp>
#include <string>

nm::optional<std::string> readFile(std::string path);

#endif // TESTUTILS_HPP

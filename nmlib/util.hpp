/**
 * @file util.hpp
 * @brief Utility headers
 * @ingroup util
 *
 * @defgroup util util
 * @brief utility functions and classes needed by other nmlib modules.
 */

#ifndef UTIL_HPP
#define UTIL_HPP

#include <nmlib/util/noncopyable.hpp>
#include <nmlib/util/userdataprovider.hpp>

#include <memory>
#include <optional>

//signals is very expensive, so don't include unless needed
//#include <nmlib/util/signals.hpp>

namespace nm {
    using std::make_unique;
    using std::optional;
} // namespace nm

#endif // UTIL_HPP

#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wshadow"
#include <boost/signals2.hpp>

namespace nm{
using boost::signals2::signal;
}

#endif // SIGNALS_HPP

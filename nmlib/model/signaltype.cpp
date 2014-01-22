#include <nmlib/signaltype.hpp>

namespace nm {

SignalType::SignalType(int dimensionality):dimensionality(dimensionality)
{
}

bool SignalType::operator==(const SignalType &rhs) const
{
    return dimensionality==rhs.dimensionality;
}

bool SignalType::isConvertibleTo(const SignalType &rhs) const
{
    return *this == rhs;
}

} // namespace nm

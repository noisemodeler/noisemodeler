#include <nmlib/model/signaltype.hpp>

namespace nm {

SignalType::SignalType(int dimensions):dimensionality(dimensions)
{
}

bool SignalType::operator==(const SignalType &rhs) const
{
    return dimensionality==rhs.dimensionality;
}

bool SignalType::operator!=(const SignalType &rhs) const
{
    return !(*this==rhs);
}

bool SignalType::isConvertibleTo(const SignalType &rhs) const
{
    return *this == rhs;
}

} // namespace nm

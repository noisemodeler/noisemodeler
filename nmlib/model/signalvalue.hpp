#ifndef NM_SIGNALVALUE_HPP
#define NM_SIGNALVALUE_HPP

#include <nmlib/model/signaltype.hpp>

#include <vector>

namespace nm {

class SignalValue
{
public:
    SignalValue(SignalType signalType):
        m_signalType(signalType),
        m_values(static_cast<unsigned int>(signalType.dimensionality))
    {}
    float &operator [](unsigned int i) {
        return m_values[i];
    }
    float operator[](unsigned int i) const {
        return m_values[i];
    }
    SignalType getSignalType() const { return m_signalType; }

private:
    const SignalType m_signalType;
    std::vector<float> m_values;
};

} // namespace nm

#endif // NM_SIGNALVALUE_HPP

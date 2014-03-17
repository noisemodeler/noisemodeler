#ifndef NM_SIGNALVALUE_HPP
#define NM_SIGNALVALUE_HPP

#include <nmlib/model/signaltype.hpp>

#include <vector>
#include <cassert>

namespace nm {

class SignalValue
{
public:
    SignalValue(float value):
        SignalValue(std::vector<float>{value})
    {}
    SignalValue(std::vector<float> values):
        m_signalType(SignalType{static_cast<int>(values.size())}),
        m_values(values)
    {}
    SignalValue(SignalType signalType):
        m_signalType(signalType),
        m_values(static_cast<unsigned int>(signalType.dimensionality))
    {}
    SignalValue(const SignalValue &other):
        m_signalType(other.m_signalType),
        m_values(other.m_values)
    {}
    SignalValue& operator=(const SignalValue &rhs){
        assert(rhs.m_signalType.isConvertibleTo(m_signalType));
        m_values = rhs.m_values;
        return *this;
    }
    //TODO move constructor

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

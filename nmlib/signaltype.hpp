#ifndef NM_SIGNALTYPE_HPP
#define NM_SIGNALTYPE_HPP

namespace nm {

class SignalType
{
public:
    const int dimensionality;
    SignalType(int dimensionality);
    bool operator==(const SignalType& rhs) const;
    bool isConvertibleTo(const SignalType &rhs) const;
};

} // namespace nm

#endif // NM_SIGNALTYPE_HPP

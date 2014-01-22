#ifndef NM_SIGNALTYPE_HPP
#define NM_SIGNALTYPE_HPP

namespace nm {

/**
 * @brief Describes a the dimensionality of a signal
 *
 * Can be extended to include other type information such as distinctions between doubles, flots and ints as well.
 */
class SignalType
{
public:
    const int dimensionality;
    SignalType(int dimensionality);
    bool operator==(const SignalType& rhs) const;

    /**
     * @brief Checks if this SignalType can be converted to another.
     * @param SignalType to convert to
     * @return
     */
    bool isConvertibleTo(const SignalType &rhs) const;
};

} // namespace nm

#endif // NM_SIGNALTYPE_HPP

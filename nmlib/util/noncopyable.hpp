#ifndef NM_NONCOPYABLE_H
#define NM_NONCOPYABLE_H

namespace nm {

/**
 * @brief A super-class for non-copyable classes
 * @ingroup util
 */
class NonCopyable
{
protected:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;
private:
    NonCopyable( const NonCopyable& other ) = delete; // non construction-copyable
    NonCopyable& operator=( const NonCopyable& ) = delete; // non copyable;
};

} // namespace nm

#endif // NM_NONCOPYABLE_H

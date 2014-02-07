#ifndef NM_NONCOPYABLE_H
#define NM_NONCOPYABLE_H

namespace nm {

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

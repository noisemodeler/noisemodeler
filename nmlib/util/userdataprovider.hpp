#ifndef NM_USERDATAPROVIDER_HPP
#define NM_USERDATAPROVIDER_HPP

namespace nm {

/**
 * @brief Base class for stuff that needs to provide user data in form of a void* pointer
 * @ingroup util
 */
class UserDataProvider
{
public:
    public:
    virtual ~UserDataProvider(){}
    void* getUserData() const {return m_userData;}
    void setUserData(void* userData) {m_userData = userData;}
//    UserDataProvider (const UserDataProvider& other):m_userData(other.m_userData){}
//    UserDataProvider& operator=(const UserDataProvider&){return *this;}
protected:
    UserDataProvider():m_userData(nullptr){}
private:
    void* m_userData;
};

} // namespace nm

#endif // NM_USERDATAPROVIDER_HPP

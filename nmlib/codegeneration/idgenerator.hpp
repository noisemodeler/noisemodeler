#ifndef NM_IDGENERATOR_HPP
#define NM_IDGENERATOR_HPP

#include <string>

namespace nm {

/**
 * @brief The IdGenerator class
 * @ingroup codegeneration
 */
class IdGenerator {
public:
    explicit IdGenerator(std::string prefix="nm_id_"):
        m_prefix(prefix),
        m_i(0)
    {}
    std::string getUniqueId() {
        return m_prefix + std::to_string(m_i++);
    }
private:
    std::string m_prefix;
    long m_i;
};

} // namespace nm

#endif // NM_IDGENERATOR_HPP

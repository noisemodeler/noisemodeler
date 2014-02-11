#ifndef NM_INLINEGENERATOR_HPP
#define NM_INLINEGENERATOR_HPP

#include <nmlib/codegeneration/idgenerator.hpp>

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/builtinmoduletype.hpp>

namespace nm {

class InlineGenerator {
public:
    struct InputConversion {
        std::string externalSymbol;
        InputLink* inputLink;
    };
    struct OutputConversion {
        std::string externalSymbol;
        OutputLink* outputLink;
    };
    explicit InlineGenerator();
    void generateModule(const std::vector<InputConversion> &inputConversions, const std::vector<OutputConversion> &outputConversions, std::ostream &out);
private:
    void generatePreamble(const std::vector<InputConversion> &inputConversions, const std::vector<OutputConversion> &outputConversions, std::ostream &out);
    void generateBody(std::ostream &out);
    void generatePostamble(std::vector<OutputConversion> conversions, std::ostream &out);

    void generateOutputDeclarations(const std::vector<OutputConversion> &conversions, std::ostream& out);
    void generateInputAssignments(const std::vector<InputConversion> &conversions, std::ostream& out);
    void generateOutputAssignments(const std::vector<OutputConversion> &conversions, std::ostream& out);
    void generateTypeKeyword(const SignalType &signalType, std::ostream& out);

    IdGenerator m_idGenerator;
};

} // namespace nm

#endif // NM_INLINEGENERATOR_HPP

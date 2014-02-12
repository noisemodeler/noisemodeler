#ifndef NM_INLINEGENERATOR_HPP
#define NM_INLINEGENERATOR_HPP

#include <nmlib/codegeneration/idgenerator.hpp>

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/builtinmoduletype.hpp>

namespace nm {

class InlineGenerator {
public:
    struct InputRemap {
        std::string externalName;
        InputLink* inputLink;
    };
    struct OutputRemap {
        std::string externalName;
        OutputLink* outputLink;
    };
    explicit InlineGenerator();
    void generateModule(const std::vector<InputRemap> &inputRemaps, const std::vector<OutputRemap> &outputRemaps, std::ostream &out);
private:
    void generatePreamble(const std::vector<InputRemap> &inputRemaps, const std::vector<OutputRemap> &outputRemaps, std::ostream &out);
    void generateBody(std::ostream &out);
    void generatePostamble(std::vector<OutputRemap> conversions, std::ostream &out);

    void generateOutputDeclarations(const std::vector<OutputRemap> &conversions, std::ostream& out);
    void generateInputDeclarations(const std::vector<InputRemap> &inputRemaps, std::ostream& out);
    void generateInputAssignments(const std::vector<InputRemap> &conversions, std::ostream& out);
    void generateOutputAssignments(const std::vector<OutputRemap> &conversions, std::ostream& out);
    void generateTypeKeyword(const SignalType &signalType, std::ostream& out);

    IdGenerator m_idGenerator;
};

} // namespace nm

#endif // NM_INLINEGENERATOR_HPP

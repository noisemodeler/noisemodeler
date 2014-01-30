#ifndef NM_COMPOSITEMODULETYPE_HPP
#define NM_COMPOSITEMODULETYPE_HPP

#include <nmlib/model/moduletype.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

namespace nm {

class InputLink;
class OutputLink;

class CompositeModuleType : public ModuleType
{
public:
    explicit CompositeModuleType(const std::string &name, const std::string &description);

    virtual std::string getName() const override {return m_name;}
    virtual std::string getDescription() const override {return m_description;}
    virtual const ModuleInput *getInput(std::string name) const override;
    virtual const ModuleOutput *getOutput(std::string name) const override;

    bool exportInput(const InputLink &inputLink, std::string externalName);
    bool exportOutput(const OutputLink &outputLink, std::string externalName);
private:
    const std::string m_name;
    const std::string m_description;
    std::vector<std::pair<ModuleInput, InputLink&>> m_inputs;
    std::vector<std::pair<ModuleOutput, OutputLink&>> m_outputs;
};

} // namespace nm

#endif // NM_COMPOSITEMODULETYPE_HPP

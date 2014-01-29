#ifndef NM_COMPOSITEMODULETYPE_HPP
#define NM_COMPOSITEMODULETYPE_HPP

#include <nmlib/model/moduletype.hpp>

namespace nm {

class CompositeModuleType : public ModuleType
{
public:
    explicit CompositeModuleType(const std::string &name, const std::string &description);

    virtual std::string getName() const override {return m_name;}
    virtual std::string getDescription() const override {return m_description;}
    virtual const ModuleInput *getInput(std::string name) const override;
    virtual const ModuleOutput *getOutput(std::string name) const override;

    bool addInput(const ModuleInput &input);
    bool addOutput(const ModuleOutput &output);
private:
    const std::string m_name;
    const std::string m_description;
    std::vector<ModuleInput> m_inputs;
    std::vector<ModuleOutput> m_outputs;
};

} // namespace nm

#endif // NM_COMPOSITEMODULETYPE_HPP

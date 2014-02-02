#ifndef NM_INPUTMODULETYPE_HPP
#define NM_INPUTMODULETYPE_HPP

#include<nmlib/model/moduletype.hpp>
#include<nmlib/model/signaltype.hpp>

namespace nm {

class InputModuleType : public ModuleType
{
public:

    // ModuleType interface
    virtual std::string getName() const override;
    virtual std::string getDescription() const override;
    virtual const ModuleInput *getInput(std::string name) const override;
    virtual const ModuleOutput *getOutput(std::string) const override;
    virtual std::vector<const ModuleOutput*> outputs() const override;
    virtual std::vector<const ModuleInput*> inputs() const override;

    bool addInput(std::string name, SignalType signalType);

private:
    explicit InputModuleType(const ModuleType& parentType);
    const ModuleType& c_parentType;
    std::vector<std::pair<ModuleInput, ModuleOutput>> m_inputs;

    friend class CompositeModuleType;
};

} // namespace nm

#endif // NM_INPUTMODULETYPE_HPP

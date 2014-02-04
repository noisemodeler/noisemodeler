#ifndef NM_BUILTINMODULETYPE_HPP
#define NM_BUILTINMODULETYPE_HPP

#include <nmlib/model/moduletype.hpp>

#include <nmlib/model/signaltype.hpp>

#include <vector>
#include <memory>

namespace nm {

class BuiltinModuleType : public ModuleType
{
public:
    explicit BuiltinModuleType(std::string name, std::string description);

    // ModuleType interface
    virtual std::string getName() const override{return c_name;}
    virtual std::string getDescription() const override{return c_description;}
    virtual const ModuleInput *getInput(std::string name) const override;
    virtual const ModuleOutput *getOutput(std::string name) const override;
    virtual std::vector<const ModuleOutput *> outputs() const override;
    virtual std::vector<const ModuleInput *> inputs() const override;
    virtual void onCreatedModule(Module &/*module*/) override {}
    virtual void onDestroyingModule(Module */*module*/) override {}

    bool addInput(std::string name, SignalType signalType);
    bool addOutput(std::string name, SignalType signalType);

private:
    const std::string c_name;
    const std::string c_description;
    std::vector<std::unique_ptr<const ModuleInput>> m_inputs;
    std::vector<std::unique_ptr<const ModuleOutput>> m_outputs;
};

} // namespace nm

#endif // NM_BUILTINMODULETYPE_HPP

#ifndef NM_PRIMITIVEMODULETYPE_HPP
#define NM_PRIMITIVEMODULETYPE_HPP

#include <nmlib/model/moduletype.hpp>

#include <nmlib/model/signaltype.hpp>

#include <vector>
#include <memory>

namespace nm {

class PrimitiveModuleType
{
public:
    explicit PrimitiveModuleType(std::string name, std::string description);

    // ModuleType interface
    virtual std::string getName() const{return c_name;}
    virtual std::string getDescription() const{return c_description;}
    virtual const ModuleInput *getInput(std::string name) const;
    virtual const ModuleOutput *getOutput(std::string name) const;
    virtual std::vector<ModuleOutput *> outputs();
    virtual std::vector<ModuleInput *> inputs();

    bool addInput(std::string name, SignalType signalType);
    bool addOutput(std::string name, SignalType signalType);

private:
    const std::string c_name;
    const std::string c_description;
    std::vector<std::unique_ptr<ModuleInput>> m_inputs;
    std::vector<std::unique_ptr<ModuleOutput>> m_outputs;
};

} // namespace nm

#endif // NM_PRIMITIVEMODULETYPE_HPP

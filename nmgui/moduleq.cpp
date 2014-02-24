#include "moduleq.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"
#include "moduletypeq.hpp"

#include <nmlib/model/module.hpp>

namespace nmgui {

ModuleQ::ModuleQ(nm::Module *module, QObject *p) :
    QObject(p),
    p_module(module)
{
    Q_ASSERT(p_module!=nullptr);
    p_module->setUserData(this);
    moduleDestroyedConnection = p_module->destroying.connect([&](nm::Module&){
        deleteLater();
        p_module->setUserData(nullptr);
        p_module = nullptr;
    });
    dependenciesChangedConnection = p_module->dependenciesChanged.connect([&](nm::Module&){
        dependenciesChanged();
    });

    inputAddedCon = p_module->addedInputLink.connect([&](nm::Module&, nm::InputLink&){
        inputsChanged();
    });
    inputRemovedCon = p_module->removedInputLink.connect([&](nm::Module&, nm::InputLink&){
        inputsChanged();
    });
    outputAddedCon = p_module->addedOutputLink.connect([&](nm::Module&, nm::OutputLink&){
        outputsChanged();
    });
    outputRemovedCon = p_module->removedOutputLink.connect([&](nm::Module&, nm::OutputLink&){
        outputsChanged();
    });

    nameChangedCon = p_module->nameChanged.connect([&](nm::Module&, const std::string&){
        nameChanged();
    });
    descriptionChangedCon = p_module->descriptionChanged.connect([&](nm::Module&, const std::string&){
        descriptionChanged();
    });
}

ModuleQ::ModuleQ(ModuleTypeQ &/*type*/, QObject */*parent*/)
{
    //TODO
    std::cerr << "not implemented\n";
}

ModuleQ::~ModuleQ()
{
    if(p_module!=nullptr){
        p_module->setUserData(nullptr);
    }
}

ModuleQ *ModuleQ::fromModule(nm::Module &module)
{
    //TODO switch to some Qt smart pointer instead of rawpointer?
    auto userData = static_cast<ModuleQ*>(module.getUserData());
    return userData != nullptr ? userData : new ModuleQ(&module);
}

void ModuleQ::setName(const QString &value)
{
    if(value == name())return;
    p_module->setName(value.toUtf8().constData());
}

QString ModuleQ::description() const
{
    auto ss = p_module->getDescription();
    return QString::fromUtf8(ss.data(), ss.size());
}

void ModuleQ::setDescription(const QString &value)
{
    if(value == description())return;
    p_module->setDescription(value.toUtf8().constData());
}

ModuleTypeQ *ModuleQ::moduleType()
{
    return ModuleTypeQ::fromModuleType(p_module->getType());
}

int ModuleQ::getDepth()
{
    return p_module->getDepth();
}

QString ModuleQ::name() const
{
    auto ss = p_module->getName();
    return QString::fromUtf8(ss.data(), ss.size());
}

QQmlListProperty<InputLinkQ> ModuleQ::inputs()
{
    return QQmlListProperty<InputLinkQ>(this, 0, nullptr, &ModuleQ::inputsCount, &ModuleQ::inputAt, nullptr);
}

InputLinkQ* ModuleQ::inputAt(QQmlListProperty<InputLinkQ> *list, int index)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        auto inputLink = module->p_module->getInput(index);
        Q_ASSERT(inputLink!=nullptr);
        return InputLinkQ::fromInputLink(*inputLink);
    } else {
        return nullptr;
    }
}

int ModuleQ::inputsCount(QQmlListProperty<InputLinkQ> *list)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        return module->p_module->getInputSize();
    } else {
        return 0;
    }
}

QQmlListProperty<OutputLinkQ> ModuleQ::outputs()
{
    return QQmlListProperty<OutputLinkQ>(this, 0, nullptr, &ModuleQ::outputsCount, &ModuleQ::outputAt, nullptr);
}

OutputLinkQ* ModuleQ::outputAt(QQmlListProperty<OutputLinkQ> *list, int index)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        auto outputLink = module->p_module->getOutput(index);
        return outputLink != nullptr ? OutputLinkQ::fromOutputLink(*outputLink) : nullptr;
    } else {
        return nullptr;
    }
}

int ModuleQ::outputsCount(QQmlListProperty<OutputLinkQ> *list)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        return module->p_module->getOutputSize();
    } else {
        return 0;
    }
}

} // namespace nmgui

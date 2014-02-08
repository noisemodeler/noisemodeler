#include "moduleq.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"

#include <nmlib/model/module.hpp>

namespace nmgui {

ModuleQ::ModuleQ(nm::Module *module, QObject *p) :
    QObject(p),
    p_module(module)
{
    Q_ASSERT(p_module!=nullptr);
    p_module->setUserData(this);
    moduleDestroyedConnection = module->destroying.connect([&](nm::Module&){
        deleteLater();
});
}

ModuleQ::~ModuleQ()
{
    p_module->setUserData(nullptr);
}

void ModuleQ::setName(const QString &value)
{
    if(value == name())return;
    p_module->setName(value.toUtf8().constData());
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

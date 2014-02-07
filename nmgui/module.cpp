#include "moduleq.hpp"
#include "inputlinkq.hpp"

namespace nmgui {

ModuleQ::ModuleQ(nm::Module *module, QObject *p) :
    QObject(p),
    p_module(module)
{
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
    return QQmlListProperty<InputLinkQ>(this, 0, &ModuleQ::append_input, &ModuleQ::inputsCount, &ModuleQ::inputAt, &ModuleQ::clearInputs);
}

void ModuleQ::append_input(QQmlListProperty<InputLinkQ> *list, InputLinkQ *input)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        module->m_inputs.append(input);
        emit module->inputsChanged();
    }
}

InputLinkQ* ModuleQ::inputAt(QQmlListProperty<InputLinkQ> *list, int index)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        return module->m_inputs.at(index);
    } else {
        return NULL;
    }
}

int ModuleQ::inputsCount(QQmlListProperty<InputLinkQ> *list)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        return module->m_inputs.count();
    } else {
        return 0;
    }
}

void ModuleQ::clearInputs(QQmlListProperty<InputLinkQ> *list)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        module->m_inputs.clear();
    }
}

QQmlListProperty<OutputLinkQ> ModuleQ::outputs()
{
    return QQmlListProperty<OutputLinkQ>(this, 0, &ModuleQ::append_output, &ModuleQ::outputsCount, &ModuleQ::outputAt, &ModuleQ::clearOutputs);
}

void ModuleQ::append_output(QQmlListProperty<OutputLinkQ> *list, OutputLinkQ *output)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        module->m_outputs.append(output);
        emit module->outputsChanged();
    }
}

OutputLinkQ* ModuleQ::outputAt(QQmlListProperty<OutputLinkQ> *list, int index)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        return module->m_outputs.at(index);
    } else {
        return NULL;
    }
}

int ModuleQ::outputsCount(QQmlListProperty<OutputLinkQ> *list)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        return module->m_outputs.count();
    } else {
        return 0;
    }
}

void ModuleQ::clearOutputs(QQmlListProperty<OutputLinkQ> *list)
{
    ModuleQ *module = qobject_cast<ModuleQ *>(list->object);
    if(module){
        module->m_outputs.clear();
    }
}



} // namespace nmgui

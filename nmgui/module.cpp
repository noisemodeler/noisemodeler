#include "module.hpp"

#include "moduleinput.hpp"

namespace nmgui {

Module::Module(nm::Module *module, QObject *p) :
    QObject(p),
    p_module(module)
{
}

void Module::setName(const QString &value)
{
    if(value == name())return;
    p_module->setName(value.toUtf8().constData());
}

QString Module::name() const
{
    auto ss = p_module->getName();
    return QString::fromUtf8(ss.data(), ss.size());
}

QQmlListProperty<ModuleInputQ> Module::inputs()
{
    return QQmlListProperty<ModuleInputQ>(this, 0, &Module::append_input, &Module::inputsCount, &Module::inputAt, &Module::clearInputs);
}

void Module::append_input(QQmlListProperty<ModuleInputQ> *list, ModuleInputQ *input)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        module->m_inputs.append(input);
        emit module->inputsChanged();
    }
}

ModuleInputQ* Module::inputAt(QQmlListProperty<ModuleInputQ> *list, int index)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        return module->m_inputs.at(index);
    } else {
        return NULL;
    }
}

int Module::inputsCount(QQmlListProperty<ModuleInputQ> *list)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        return module->m_inputs.count();
    } else {
        return 0;
    }
}

void Module::clearInputs(QQmlListProperty<ModuleInputQ> *list)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        module->m_inputs.clear();
    }
}

QQmlListProperty<ModuleOutputQ> Module::outputs()
{
    return QQmlListProperty<ModuleOutputQ>(this, 0, &Module::append_output, &Module::outputsCount, &Module::outputAt, &Module::clearOutputs);
}

void Module::append_output(QQmlListProperty<ModuleOutputQ> *list, ModuleOutputQ *output)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        module->m_outputs.append(output);
        emit module->outputsChanged();
    }
}

ModuleOutputQ* Module::outputAt(QQmlListProperty<ModuleOutputQ> *list, int index)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        return module->m_outputs.at(index);
    } else {
        return NULL;
    }
}

int Module::outputsCount(QQmlListProperty<ModuleOutputQ> *list)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        return module->m_outputs.count();
    } else {
        return 0;
    }
}

void Module::clearOutputs(QQmlListProperty<ModuleOutputQ> *list)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        module->m_outputs.clear();
    }
}



} // namespace nmgui

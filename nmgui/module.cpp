#include "module.hpp"

#include "moduleinput.hpp"

namespace nmgui {

Module::Module(QObject *p) :
    QObject(p)
{
}

void Module::setName(const QString &value)
{
    if(value != m_name){
        m_name = value;
        emit nameChanged();
    }
}

QString Module::name() const
{
    return m_name;
}

QQmlListProperty<ModuleInput> Module::inputs()
{
    return QQmlListProperty<ModuleInput>(this, 0, &Module::append_input, &Module::inputsCount, &Module::inputAt, &Module::clearInputs);
}

void Module::append_input(QQmlListProperty<ModuleInput> *list, ModuleInput *input)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        module->m_inputs.append(input);
        emit module->inputsChanged();
    }
}

ModuleInput* Module::inputAt(QQmlListProperty<ModuleInput> *list, int index)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        return module->m_inputs.at(index);
    } else {
        return NULL;
    }
}

int Module::inputsCount(QQmlListProperty<ModuleInput> *list)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        return module->m_inputs.count();
    } else {
        return 0;
    }
}

void Module::clearInputs(QQmlListProperty<ModuleInput> *list)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        module->m_inputs.clear();
    }
}

QQmlListProperty<ModuleOutput> Module::outputs()
{
    return QQmlListProperty<ModuleOutput>(this, 0, &Module::append_output, &Module::outputsCount, &Module::outputAt, &Module::clearOutputs);
}

void Module::append_output(QQmlListProperty<ModuleOutput> *list, ModuleOutput *output)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        module->m_outputs.append(output);
        emit module->outputsChanged();
    }
}

ModuleOutput* Module::outputAt(QQmlListProperty<ModuleOutput> *list, int index)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        return module->m_outputs.at(index);
    } else {
        return NULL;
    }
}

int Module::outputsCount(QQmlListProperty<ModuleOutput> *list)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        return module->m_outputs.count();
    } else {
        return 0;
    }
}

void Module::clearOutputs(QQmlListProperty<ModuleOutput> *list)
{
    Module *module = qobject_cast<Module *>(list->object);
    if(module){
        module->m_outputs.clear();
    }
}



} // namespace nmgui

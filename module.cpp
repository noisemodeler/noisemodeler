#include "module.h"

#include "moduleinput.h"

namespace nmgui {

Module::Module(QObject *parent) :
    QObject(parent)
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

} // namespace nmgui

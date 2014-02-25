#include "moduleinputq.hpp"

#include <nmlib/model/moduleinput.hpp>

namespace nmgui {

ModuleInputQ::ModuleInputQ(nm::ModuleInput *moduleInput, QObject *parent) :
    QObject(parent),
    m_moduleInput(moduleInput)
{
    Q_ASSERT(m_moduleInput!=nullptr);
    Q_ASSERT(m_moduleInput->getUserData()==nullptr);
    m_moduleInput->setUserData(this);

    moduleInputDestroyingConnection = m_moduleInput->destroying.connect([&](nm::ModuleInput &){
        deleteLater();
        m_moduleInput->setUserData(nullptr);
        m_moduleInput = nullptr;
//        delete this;
    });
}

ModuleInputQ *ModuleInputQ::fromModuleInput(nm::ModuleInput &moduleInput)
{
    //TODO switch to some Qt smart pointer instead of rawpointer?
    auto userData = static_cast<ModuleInputQ*>(moduleInput.getUserData());
    return userData != nullptr ? userData : new ModuleInputQ(&moduleInput);
}

QString ModuleInputQ::name() const
{
    auto ss = m_moduleInput->getName();
    return QString::fromUtf8(ss.data(), ss.size());
}

} // namespace nmgui

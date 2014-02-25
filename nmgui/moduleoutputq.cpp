#include "moduleoutputq.hpp"

#include <nmlib/model/moduleoutput.hpp>

namespace nmgui {

ModuleOutputQ::ModuleOutputQ(nm::ModuleOutput *moduleOutput, QObject *parent) :
    QObject(parent),
    m_moduleOutput(moduleOutput)
{
    Q_ASSERT(m_moduleOutput!=nullptr);
    Q_ASSERT(m_moduleOutput->getUserData()==nullptr);
    m_moduleOutput->setUserData(this);

    moduleOutputDestroyingConnection = m_moduleOutput->destroying.connect([&](nm::ModuleOutput &){
        deleteLater();
        m_moduleOutput->setUserData(nullptr);
        m_moduleOutput = nullptr;
//        delete this;
    });
}

ModuleOutputQ *ModuleOutputQ::fromModuleOutput(nm::ModuleOutput &moduleOutput)
{
    //TODO switch to some Qt smart pointer instead of rawpointer?
    auto userData = static_cast<ModuleOutputQ*>(moduleOutput.getUserData());
    return userData != nullptr ? userData : new ModuleOutputQ(&moduleOutput);
}

QString ModuleOutputQ::name() const
{
    auto ss = m_moduleOutput->getName();
    return QString::fromUtf8(ss.data(), ss.size());
}

}

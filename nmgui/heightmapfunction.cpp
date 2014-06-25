#include "heightmapfunction.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"
#include "moduleq.hpp"

namespace nmgui {

HeightMapFunction::HeightMapFunction(QObject *parent) :
    QObject(parent),
    m_inputLink(nullptr),
    m_outputLink(nullptr)
{
    connect(this, SIGNAL(inputLinkChanged()), this, SIGNAL(functionChanged()));
    connect(this, SIGNAL(outputLinkChanged()), this, SIGNAL(functionChanged()));
}

bool HeightMapFunction::valid() const
{
    return m_inputLink != nullptr &&
            m_outputLink != nullptr &&
            m_inputLink->inputLink() != nullptr &&
            m_outputLink->outputLink() != nullptr;
}


void HeightMapFunction::setInputLink(InputLinkQ *newLink)
{
    if(newLink==m_inputLink){
        return;
    }
    m_inputLink = newLink;
    emit inputLinkChanged();
}

void HeightMapFunction::setOutputLink(OutputLinkQ *newLink)
{
    if(newLink==m_outputLink){
        return;
    }
    //disconnect all signals, since we are about to forget about this input
    if(m_outputLink!=nullptr)disconnect(m_outputLink->owner(), 0, this, 0);
    m_outputLink = newLink;
    //forward signal to listeners of this object
    connect(m_outputLink->owner(), SIGNAL(dependenciesChanged()), this, SIGNAL(functionChanged()));
    emit outputLinkChanged();
}

} // namespace nmgui

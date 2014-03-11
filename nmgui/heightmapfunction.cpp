#include "heightmapfunction.hpp"

#include <moduleq.hpp>

namespace nmgui {

HeightMapFunction::HeightMapFunction(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(inputLinkChanged()), this, SIGNAL(functionChanged()));
    connect(this, SIGNAL(outputLinkChanged()), this, SIGNAL(functionChanged()));
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

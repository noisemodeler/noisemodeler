#include "document.hpp"

#include <nmlib/serialization.hpp>

#include <iostream> //TODO remove
#include <QFile>
#include <QTextStream>

namespace nmgui {

Document::Document(QString filePath, QObject *parent) :
    QObject(parent),
    m_filePath(filePath)
{
    open(filePath);
}

TypeManagerQ *Document::typeManager(){ return m_typeManager ? TypeManagerQ::fromTypeManager(*m_typeManager) : nullptr; }

void Document::saveAs(QString filePath)
{
    m_filePath = filePath;
    nm::Serializer serializer;
    std::string json = serializer.serialize(*m_typeManager);

    //save to disk

//    if (filePath.name().size() == 0) {
//        qWarning() << "Cannot save file, empty filename.";
//        return;
//    }

//    QString extendedName = currentFile.name();
//    if (!currentFile.name().endsWith(".txt")) {
//        extendedName.append(".txt");
//    }

    //move to save function?
    QFile file(m_filePath);
    if(!file.open(QFile::WriteOnly | QIODevice::Text)) {
        std::cerr << "Couldn't write to file: " << filePath.toStdString() << "\n";
        return;
    }
    QTextStream outStream(&file);
    outStream << json.c_str();
    file.close();
}

void Document::saveAsQmlUrl(QString filePath)
{
    //just remove the stupid file:// prefix
    saveAs(filePath.mid(7));
}

void Document::open(QString filePath)
{
    nm::Parser parser;
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        //TODO error handling
    }
    QTextStream in(&file);
    QString blankDocumentString = in.readAll();
    auto maybeTypeManager = parser.parseDocument(blankDocumentString.toStdString());
    if(!maybeTypeManager){
        //TODO error handling
    }
    m_typeManager = std::move(*maybeTypeManager);
    emit typeManagerChanged();
}

void Document::openQmlUrl(QString filePath)
{
    open(filePath.mid(7));
}

} // namespace nmgui

#ifndef NMGUI_DOCUMENT_HPP
#define NMGUI_DOCUMENT_HPP

#include "typemanagerq.hpp"

#include <nmlib/model/typemanager.hpp>

#include <QObject>

namespace nmgui {

class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(QString filePath, QObject *parent = 0);
    TypeManagerQ* typeManager();

public slots:
    void saveAs(QString filePath);
    void saveAsQmlUrl(QString filePath);

private:
    QString m_filePath;
    std::unique_ptr<nm::TypeManager> m_typeManager;
};

} // namespace nmgui

#endif // NMGUI_DOCUMENT_HPP

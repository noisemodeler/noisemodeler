#ifndef NMGUI_DOCUMENT_HPP
#define NMGUI_DOCUMENT_HPP

#include <nmlib/model/typemanager.hpp>

#include <QObject>

namespace nmgui {

class TypeManagerQ;

class Document : public QObject
{
    Q_OBJECT
    Q_PROPERTY(nmgui::TypeManagerQ *typeManager READ typeManager NOTIFY typeManagerChanged)
public:
    explicit Document(QString filePath, QObject *parent = nullptr);
    TypeManagerQ* typeManager();

signals:
    void typeManagerChanged();

public slots:
    void saveAs(QString filePath);
    void saveAsQmlUrl(QString filePath);
    void open(QString filePath);
    void openQmlUrl(QString filePath);

private:
    QString m_filePath;
    std::unique_ptr<nm::TypeManager> m_typeManager;
};

} // namespace nmgui

#endif // NMGUI_DOCUMENT_HPP

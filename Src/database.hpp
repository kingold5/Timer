#ifndef DATABASE_H
#define DATABASE_H

#include <QtXml>
#include "projectsstruct.h"

class DataBase
{
public:
    DataBase();

    bool initDBFiles();
    int loadTemp(QString &projectName, Time &projectTime);
    int loadTemp(QString &projectName, QString &projectTime);
    int append(const QString &fileName, const QString &projectName, const Time &projectTime);
    int append(const QString &fileName, const QString &projectName, const QString &projectTime);
    bool dataExisted(QDomElement& root, const QString& projectName);
    QDomDocument getDocHistory();
    QDomDocument getDocUser();
    static QString toTimeQString(const Time &timeDigital);
    static bool toTimeDigital(const QString &timeQString, Time &timeDigital);
    static bool loadDocuments(QFile &file, QDomDocument &doc, QIODevice::OpenMode mode);

    static const QString k_fileDir;
    static const QString k_tempFile;
    static const QString k_userFile;

private:
    QDomElement nodeProject(QDomDocument &doc, const QString &projectName, const QString &projectTime);
    bool initHistoryFiles();
    bool initUserFiles();
    bool loadDocuments(const QString &fileName, QDomDocument &doc);
    bool saveDocuments(const QString &fileName, const QDomDocument &doc);

    QDomDocument docHistory;
    QDomDocument docUser;
};
#endif // DATABASE_H

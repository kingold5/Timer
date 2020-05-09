#ifndef DATABASE_H
#define DATABASE_H

#include <QtXml>
#include "projectsstruct.h"

class DataBase
{
public:
    DataBase();

    void setProject(const QString& projectName, const QString& projectTime);
    int loadTemp(QString &projectName, Time &projectTime);
    int loadTemp(QString &projectName, QString &projectTime);
    int append(const QString &fileName, const QString &projectName, const Time &projectTime);
    int append(const QString &fileName, const QString &projectName, const QString &projectTime);
    int loadAll(const QString &fileName, QVector<Projects> &projectAll);
    bool dataExisted(QDomElement& root, const QString& projectName);
    QString toTimeQString(const Time &timeDigital);
    bool toTimeDigital(const QString &timeQString, Time &timeDigital);

private:
    QDomElement nodeProject(QDomDocument &doc, const QString &projectName, const QString &projectTime);

    QString currentName;
    QString currentDuration;
    QString oldName;
    QString oldDuration;
};
#endif // DATABASE_H

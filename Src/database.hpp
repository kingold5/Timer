#ifndef DATABASE_H
#define DATABASE_H

#include <QtXml>

class DataBase
{
public:
    DataBase();

    void setProject(const QString& projectName, const QString& projectTime);
    int appendTemp(const QString &projectName, const QString &projectTime);
    int loadTemp(QString* projectName, double* h, double* m, double* s);
    int loadTemp(QString* projectName, QString* projectTime);
    int append(const QString& projectName, const QString& projectTime);
    int append(const QString& projectName, const double &h, const double &m, const double &s);
    int load(QString* projectName, double h, double m, double s);
    bool dataExisted(QDomElement& root, const QString& projectName);
    bool toTime(QString time, double *h, double *m, double *s);

private:
    QDomElement nodeProject(QDomDocument &doc, const QString &projectName, const QString &projectTime);
    QString toQString(const double &h, const double &m, const double &s);
    QString currentName;
    QString currentDuration;
    QString oldName;
    QString oldDuration;
};
#endif // DATABASE_H

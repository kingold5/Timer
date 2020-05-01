#ifndef DATABASE_H
#define DATABASE_H

#include <QtXml>

class DataBase
{
public:
    DataBase(QWidget* p);

    int writeTemp(const QString projectName, const QString projectTime);
    int loadTemp(QString* projectName, double* h, double* m, double* s);
    int loadTemp(QString* projectName, QString* projectTime);
    int append(const QString& projectName, const QString& projectTime);
    int append(const QString& projectName, const double &h, const double &m, const double &s);
    int load(QString* projectName, double h, double m, double s);
    bool dataExisted(QDomElement& root, const QString& projectName);
    bool toTime(QString time, double *h, double *m, double *s);

private:
    QDomElement nodeProject(QDomDocument &doc, const QString &projectName, const QString &projectTime);
};

#endif // DATABASE_H

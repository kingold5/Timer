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
    int write(const QString* projectName, const QString* projectTime);
    int load(QString* projectName, double h, double m, double s);
    bool dataExisted(QDomElement& root, const QString& projectName);
    bool toTime(QString time, double *h, double *m, double *s);

private:
    QDomElement nodeProject(QDomDocument &doc, QString projectName, QString projectTime);
};

#endif // DATABASE_H

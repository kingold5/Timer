#ifndef PROJECTSTRUCT_H
#define PROJECTSTRUCT_H

#include <QString>

struct Time{
    double hour;
    double minute;
    double second;
};

struct Projects{
    int id;
    QString name;
    QString durationQString;
    Time durationDigital;
    QString createDate;
};

#endif // PROJECTSTRUCT_H

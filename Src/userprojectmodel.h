#ifndef USERPROJECTMODEL_H
#define USERPROJECTMODEL_H

#include "projectsmodel.h"

class UserProjectModel : public ProjectsModel
{
    Q_OBJECT

public:
    UserProjectModel(QDomDocument &pdoc, QObject *parent = nullptr);
};

#endif // USERPROJECTMODEL_H

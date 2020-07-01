#ifndef USERPROJECTMODEL_H
#define USERPROJECTMODEL_H

#include "projectsmodel.h"

class UserProjectModel : public ProjectsModel
{
    Q_OBJECT

public:
    UserProjectModel(QDomDocument &pdoc, QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // USERPROJECTMODEL_H

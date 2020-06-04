#ifndef PROJECTSMODEL_H
#define PROJECTSMODEL_H

#include <QDomDocument>
#include <QAbstractTableModel>
#include <QtXml>

class ProjectsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ProjectsModel(QDomDocument &pdoc, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role=Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent=QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent=QModelIndex()) override;
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;

    QDomDocument doc;
    QDomNodeList nodes;
};

#endif // PROJECTSMODEL_H

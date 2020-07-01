#include <QIcon>
#include "userprojectmodel.h"

// TODO:
// Centering Importance items

UserProjectModel::UserProjectModel(QDomDocument &pdoc, QObject *parent)
    : ProjectsModel(pdoc, parent)
{
}

QVariant UserProjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return tr("Plan Name");
        case 1:
            return tr("Duration");
        case 2:
            return tr("Importance");
        case 3:
            return tr("Time Left");
        case 4:
            return tr("Complete");
        case 5:
            return tr("Create Date");
        default:
            break;
        }
    }
    return QVariant();
}

int UserProjectModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return 6;
}

QVariant UserProjectModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    QDomElement element = nodes.at(index.row()).toElement();
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return element.attribute("name", "");
        case 1:
            return element.attribute("duration", "");
        case 3:
            return element.attribute("timeLeft", "");
        case 4:
            return element.attribute("percent100", "");
        case 5:
            return element.firstChildElement("createDate").text();
        default:
            break;
        }
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    } else if (role == Qt::DecorationRole) {
        if (index.column() == 2) {
            QString importance = element.firstChildElement("importance").text();
            if (importance == "0") {
                return QString("Default");
            } else if (importance == "1") {
                return QIcon(":/icons/Rcs/single_star.png");
            } else if (importance == "2") {
                return QIcon(":/icons/Rcs/double_stars.png");
            } else if (importance == "3") {
                return QIcon(":/icons/Rcs/triple_stars.png");
            }
        }
    }

    return QVariant();
}

#include <QDebug>
#include "database.hpp"
#include "projectsmodel.h"

ProjectsModel::ProjectsModel(QDomDocument &pdoc, QObject *parent)
    : QAbstractTableModel(parent),
      doc(pdoc)
{
    nodes = doc.elementsByTagName("projects");
}

QVariant ProjectsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return tr("Plan Name");
        case 1:
            return tr("Duration");
        case 2:
            return tr("Time Left");
        case 3:
            return tr("Complete");
        case 4:
            return tr("Create Date");
        default:
            break;
        }
    }
    return QVariant();
}

int ProjectsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return nodes.count();
}

int ProjectsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return 5;
}

QVariant ProjectsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        QDomElement element = nodes.at(index.row()).toElement();
        switch (index.column()) {
        case 0:
            return element.attribute("name", "");
        case 1:
            return element.attribute("duration", "");
        case 2:
            return element.attribute("timeLeft", "");
        case 3:
            return element.attribute("percent100", "");
        case 4:
            return element.firstChildElement("createDate").text();
        default:
            break;
        }
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    return QVariant();
}

bool ProjectsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!index.isValid()) {
            return false;
        }
        if (!value.toString().isEmpty()) {
            QDomElement element = nodes.at(index.row()).toElement();
            switch (index.column()) {
            case 0: {

                element.setAttribute("name", value.toString());
                return true;
            }
            case 1: {
                element.setAttribute("duration", value.toString());
                return true;
            }
            case 2: {
                element.setAttribute("timeLeft", value.toString());
                return true;
            }
            default:
                break;
            }
        }
    }
    return false;
}

Qt::ItemFlags ProjectsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool ProjectsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
    doc.documentElement().appendChild(DataBase::nodeProject(doc));
    endInsertRows();
    return true;
}

bool ProjectsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    /**
     * count must be 1, only remove 1 row.
     */
    beginRemoveRows(parent, row, row+count-1);
    QDomNode node = nodes.at(row);
    node.parentNode().removeChild(node);
    endRemoveRows();

    return true;
}

bool ProjectsModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    /**
     * count must be 1, only move 1 row.
     */
    beginMoveRows(sourceParent, sourceRow, sourceRow+count-1, destinationParent, destinationChild);
    QDomNode sourceNode = nodes.at(sourceRow);
    QDomNode destinationNode = nodes.at(destinationChild-1);
    destinationNode.parentNode().insertAfter(sourceNode, destinationNode);
    endMoveRows();

    return true;
}

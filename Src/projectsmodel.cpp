#include <QMessageBox>
#include <QDebug>
#include "projectsmodel.h"

ProjectsModel::ProjectsModel(QDomDocument &doc, QObject *parent)
    : QAbstractTableModel(parent)
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
    } else {
        return nodes.count();
    }
}

int ProjectsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    } else {
        return 3;
    }
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
            return element.firstChildElement("createDate").text();
        default:
            break;
        }
    } else if (role == Qt::TextAlignmentRole) {
        if (index.column()==0 || index.column()==1) {
            return Qt::AlignHCenter + Qt::AlignVCenter;
        }
    }

    return QVariant();
}

bool ProjectsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!index.isValid()) {
            return false;
        }
        qDebug() << "in setData";
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

bool ProjectsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);
    QDomNode node = nodes.at(row);
    node.parentNode().removeChild(node);
    endRemoveRows();

    return true;
}

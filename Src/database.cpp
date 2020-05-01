#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include "database.hpp"

DataBase::DataBase() :
    currentName(""),
    currentDuration(""),
    oldName(""),
    oldDuration("")
{

}

void DataBase::setProject(const QString &projectName, const QString &projectTime) {
    currentName = projectName;
    currentDuration = projectTime;
}

int DataBase::appendTemp(const QString &projectName, const QString &projectTime)
{
    QDomDocument doc;
    QFile file("tempplans.xml");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug("Open file failed");
        return -1;
    }
    if (file.size() == 0) {
        qDebug() << "file is null";
        QDomElement newRoot = doc.createElement("tempPlans");
        doc.appendChild(newRoot);
    }
    else if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "Load content failed";
        return -1;
    }

    // Find the root element
    QDomElement root = doc.documentElement();
    // Find latest project, if it is not identical to the current project
    // append the current project.
    QDomNode n = root.lastChild();
    QDomElement e = n.toElement();
    if (!e.isNull()) {
        if (e.attribute("name", "") == projectName && e.attribute("duration", "") == projectTime) {
            // Same project, no need to write
            return 1;
        }
    }

    root.appendChild(nodeProject(doc, projectName, projectTime));

    QTextStream ts(&file);
    file.resize(0);
    ts<<doc.toString();
    return 0;
}

int DataBase::loadTemp(QString* projectName, double* h, double* m, double *s) {
    /**
     * Load the lastest plan from tempplans.xml
     *
     * If the XML file is empty, or data is corrupted, load default value
     * @return 0:	load finished,
     * 		   -1:	file load problem
     * 		   1:	no data found in database
     */

    QDomDocument doc("tempPlans");
    QFile file("tempplans.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open file failed";
        return -1;
    }
    if (!doc.setContent(&file)) {
        qDebug() << "Load file failed";
        file.close();
        return -1;
    }

    // Find the root element
    QDomElement docElem = doc.documentElement();
    // Find last child node of root element
    QDomNode n = docElem.lastChild();
    QDomElement e = n.toElement();
    if (!e.isNull()) {
        QString time = e.attribute("duration", "");
        if (toTime(time, h, m, s)) {
            *projectName = e.attribute("name", "");
            return 0;
        }
    }

    return 1;
}

int DataBase::load(QString *projectName, double h, double m, double s) {
    return 0;
}

int DataBase::append(const QString &projectName, const double &h, const double &m, const double &s) {
    QString projectTime = toQString(h, m, s);
    int result = append(projectName, projectTime);
    return result;
}

QString DataBase::toQString(const double& h, const double& m, const double& s) {
    QString textTime = QString("%1:%2:%3")
            .arg(static_cast<int>(h), 2, 10, QChar('0'))
            .arg(static_cast<int>(m), 2, 10, QChar('0'))
            .arg(static_cast<int>(s), 2, 10, QChar('0'));
    return textTime;
}

int DataBase::append(const QString &projectName, const QString &projectTime) {
    /**
     * Add data into userplans.xml
     *
     * @projectName	: Project Name
     * @projectTime	: Project duration
     *
     * @return 0:	write finished,
     * 		   -1:	file load/open problem
     * 		   1:	data existed, no write needed
     */
    QDomDocument doc;
    QFile file("userplans.xml");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug("Open file failed");
        return -1;
    }
    if (file.size() == 0) {
        qDebug() << "file is null";
        QDomElement newRoot = doc.createElement("userPlans");
        doc.appendChild(newRoot);
    }
    else if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "Load content failed";
        return -1;
    }

    // Find the root element
    QDomElement root = doc.documentElement();
    if (!dataExisted(root, projectName)) {
        root.appendChild(nodeProject(doc, projectName, projectTime));
        QTextStream ts(&file);
        file.resize(0);
        ts<<doc.toString();
        return 0;
    } else {
        return 1;
    }
}

bool DataBase::dataExisted(QDomElement& root, const QString &projectName)
{
    // First child of root element
    QDomNode n = root.firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement();
        if (!e.isNull()) {
            if (e.attribute("name", "") == projectName) {
                qDebug() << "Project name exists.";
                return true;
            }
        }
        n = n.nextSibling();
    }

    qDebug() << "Project name can be used.";
    return false;
}

bool DataBase::toTime(QString time, double *h, double* m, double* s) {
    bool flagh, flagm, flags;
    if (!time.isEmpty()) {
        double hour = time.split(":")[0].toDouble(&flagh);
        double min = time.split(":")[1].toDouble(&flagm);
        double sec = time.split(":")[2].toDouble(&flags);

        if (flagh && flagm && flags) {
            *h = hour;
            *m = min;
            *s = sec;
        } else {
            return false;
        }
        return true;
    }

    return false;
}

QDomElement DataBase::nodeProject(QDomDocument &doc, const QString& projectName, const QString& projectTime) {
    // Add new project node
    QDomElement newProject = doc.createElement("projects");
    newProject.setAttribute("name", projectName);
    newProject.setAttribute("duration", projectTime);

    QDateTime createDate;
    QString QCreateDate = createDate.currentDateTimeUtc().toString();
    QDomElement date = doc.createElement("createDate");
    QDomText tCreateDate = doc.createTextNode(QCreateDate);
    newProject.appendChild(date);
    date.appendChild(tCreateDate);

    return newProject;
}

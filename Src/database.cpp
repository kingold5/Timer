#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include "database.hpp"


DataBase::DataBase(QWidget* p) : parent(p)
{
    ;
}

int DataBase::writeTemp(const QString projectName, const QString projectTime)
{
//    int result = dataExisted(projectName);
//    if (result == 0) {
//        // Project name already exists.
//        QMessageBox msgBox(parent);
//        msgBox.setIcon(QMessageBox::Warning);
//        msgBox.setText("The project name has been used");
//        msgBox.exec();
//    } else if (result == -1) {
//        // Project name is valid
//        QMessageBox msgBox(parent);
//        msgBox.setIcon(QMessageBox::Critical);
//        msgBox.setText("XML file cannot be found!");
//        msgBox.exec();
//    }
    QDomDocument doc;
    QDomElement root = doc.createElement("tempPlans");
    doc.appendChild(root);

    QDomElement user = doc.createElement("projects");
    user.setAttribute("duration", projectTime);
    user.setAttribute("name", projectName);
    root.appendChild(user);

    QDateTime createDate;
    QString QCreateDate = createDate.currentDateTimeUtc().toString();
    QDomElement date = doc.createElement("createDate");
    QDomText tCreateDate = doc.createTextNode(QCreateDate);
    user.appendChild(date);
    date.appendChild(tCreateDate);

    QFile file("tempplans.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"could not open file for Writing";
        return -1;
    }
    else
    {
        QTextStream ts(&file);
        ts<<doc.toString();
        qDebug()<<"Finished";
    }
    return 0;
}

int DataBase::loadTemp(QString* projectName, double *h, double *m, double *s) {
    /**
     * Load the lastest plan from tempplan.xml
     *
     * If the XML file is empty, or data is corrupted, load default value
     * @return 0:	load finished,
     * 		   -1:	file load problem
     */

    QDomDocument doc("tempPlans");
    QFile file("tempplans.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    if (!doc.setContent(&file)) {
        file.close();
        return -1;
    }

    // Find the root element
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.lastChild();
    QDomElement e = n.toElement();
    if (!e.isNull()) {
        QString time = e.attribute("duration", "");
        if (toTime(time, h, m, s)) {
            *projectName = e.attribute("name", "");
            return 0;
        }
     }

    // Set all value as default
    *projectName == "";
    *h = 0.0;
    *m = 0.0;
    *s = 0.0;
    return 0;
}

int DataBase::load(QString *projectName, double h, double m, double s) {
    return 0;
}

int DataBase::write(const QString *projectName, const QString *projectTime) {
    return 0;
}

int DataBase::dataExisted(const QString *projectName)
{
    QDomDocument doc("tempPlans");
    QFile file("tempplans.xml");
    if (!file.open(QIODevice::ReadOnly))
        return -1;
    if (!doc.setContent(&file)) {
        file.close();
        return -1;
    }

    // Find the root element
    QDomElement docElem = doc.documentElement();

    // First child of root element
    QDomNode n = docElem.firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement();
        if (!e.isNull()) {
            if (e.tagName() == "projects" && e.attribute("name", "") == *projectName) {
                qDebug() << "Project name exists.";
                return 0;
            }
        }
        n = n.nextSibling();
    }

    qDebug() << "Project name can be used.";
    return 1;
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

QDomElement DataBase::nodeProject(QDomDocument &doc, QString projectName, QString projectTime) {
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

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include "database.hpp"

const QString DataBase::k_fileDir = "userdata";
const QString DataBase::k_tempFile = k_fileDir + "/tempplans.xml";
const QString DataBase::k_userFile = k_fileDir + "/userplans.xml";
{

}

void DataBase::setProject(const QString &projectName, const QString &projectTime) {
    currentName = projectName;
    currentDuration = projectTime;
}

int DataBase::loadTemp(QString &projectName, Time &projectTime) {
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
        if (toTimeDigital(e.attribute("duration", ""), projectTime)) {
            projectName = e.attribute("name", "");
            return 0;
        }
    }

    return 1;
}

int DataBase::loadAll(const QString &fileName, QVector<Projects> &projectAll) {
    QFile file(fileName);
    QDomDocument doc;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open file failed";
        return -1;
    }
    if (!doc.setContent(&file)) {
        qDebug() << "Load file failed";
        file.close();
        return -1;
    }

    Time projectTime;
    QDomNodeList nodes = doc.elementsByTagName("projects");
    for (int i=0; i<nodes.count(); ++i) {
        QDomElement element = nodes.at(i).toElement();
        toTimeDigital(element.attribute("duration", ""), projectTime);
        Projects newProject = {i,
                               element.attribute("name", ""),
                               element.attribute("duration", ""),
                               projectTime,
                               element.firstChildElement("createDate").text()};

        projectAll.append(newProject);
    }

    return 0;
}

int DataBase::append(const QString &fileName, const QString &projectName, const Time &projectTime) {
    /**
     * Add data into userplans.xml/tempplans.xml
     *
     * @fileName : xml file name
     * @projectName	: Project Name
     * @h :	hour
     * @m : minute
     * @s : second
     *
     * @return 0:	write finished,
     * 		   -1:	file load/open problem
     * 		   1:	data existed, no write needed
     */
    QString timeQString = toTimeQString(projectTime);
    return append(fileName, projectName, timeQString);
}

int DataBase::append(const QString &fileName, const QString &projectName, const QString &projectTime) {
    /**
     * Add data into userplans.xml/tempplans.xml
     *
     * @fileName : xml file name
     * @projectName	: Project Name
     * @projectName : Project Time
     *
     * @return 0:	write finished,
     * 		   -1:	file load/open problem
     * 		   1:	data existed, no write needed
     */
    QString rootTag;
    if (fileName == "userplans.xml") {
        rootTag = "userPlans";
    } else if (fileName == "tempplans.xml") {
        rootTag = "tempPlans";
    } else {
        qDebug() << "Wrong filename";
        return -1;
    }

    QDomDocument doc;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug("Open file failed");
        return -1;
    }
    if (file.size() == 0) {
        qDebug() << "file is null";
        QDomElement newRoot = doc.createElement(rootTag);
        doc.appendChild(newRoot);
    }
    else if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "Load content failed";
        return -1;
    }

    // Find the root element
    QDomElement root = doc.documentElement();
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

QString DataBase::toTimeQString(const Time &timeDigital) {
    QString textTime = QString("%1:%2:%3")
            .arg(static_cast<int>(timeDigital.hour), 2, 10, QChar('0'))
            .arg(static_cast<int>(timeDigital.minute), 2, 10, QChar('0'))
            .arg(static_cast<int>(timeDigital.second), 2, 10, QChar('0'));
    return textTime;
}

bool DataBase::toTimeDigital(const QString &timeQString, Time &timeDigital) {
    bool flagh, flagm, flags;
    if (!timeQString.isEmpty()) {
        double hour = timeQString.split(":")[0].toDouble(&flagh);
        double min = timeQString.split(":")[1].toDouble(&flagm);
        double sec = timeQString.split(":")[2].toDouble(&flags);

        if (flagh && flagm && flags) {
            timeDigital.hour = hour;
            timeDigital.minute = min;
            timeDigital.second = sec;
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

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include "database.hpp"

const QString DataBase::k_fileDir = "userdata";
const QString DataBase::k_tempFile = k_fileDir + "/tempplans.xml";
const QString DataBase::k_userFile = k_fileDir + "/userplans.xml";

DataBase::DataBase()
{
}

bool DataBase::initDBFiles()
{
    if (!QDir(k_fileDir).exists() && !QDir().mkdir(k_fileDir)) {
        return false;
    }
    bool initHistory = initHistoryFiles();
    bool initUser = initUserFiles();
    return initHistory | initUser;
}

bool DataBase::initHistoryFiles()
{
    if (!QFile::exists(k_tempFile) || QFile(k_tempFile).size() == 0) {
        QFile file(k_tempFile);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Create file failed";
            file.close();
            return false;
        }
        QDomElement newRoot = docHistory.createElement("tempPlans");
        docHistory.appendChild(newRoot);
        QTextStream ts(&file);
        ts<<docHistory.toString();
        file.close();
    } else {
        loadDocuments(k_tempFile, docHistory);
    }
    return true;
}

bool DataBase::initUserFiles()
{
    if (!QFile::exists(k_userFile) || QFile(k_userFile).size() == 0) {
        QFile file(k_userFile);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Create file failed";
            file.close();
            return false;
        }
        QDomElement newRoot = docUser.createElement("userPlans");
        docUser.appendChild(newRoot);
        QTextStream ts(&file);
        ts<<docUser.toString();
        file.close();
    } else {
        loadDocuments(k_userFile, docUser);
    }
    return true;
}

bool DataBase::loadDocuments(const QString &fileName, QDomDocument &doc)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open file failed";
        return false;
    }
    if (!doc.setContent(&file)) {
        qDebug() << "Load file failed";
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool DataBase::saveDocuments(const QString &fileName, const QDomDocument &doc)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Open file failed";
        return false;
    }

    QTextStream ts(&file);
    file.resize(0);
    ts<<doc.toString();
    file.close();
    return true;
}

QDomDocument DataBase::getDocHistory()
{
    return docHistory;
}

QDomDocument DataBase::getDocUser()
{
    return docUser;
}

bool DataBase::saveDataBase(const QString &fileName)
{
    if (fileName == k_tempFile && saveDocuments(k_tempFile, docHistory)) {
        return true;
    } else if (fileName == k_userFile && saveDocuments(k_userFile, docUser)) {
        return true;
    }
    return false;
}

bool DataBase::resetDataBase(const QString &fileName)
{
    if (fileName == k_tempFile && loadDocuments(k_tempFile, docHistory)) {
        return true;
    } else if (fileName == k_userFile && loadDocuments(k_userFile, docUser)) {
        return true;
    }
    return false;
}

bool DataBase::updateDataBase()
{
    /***
     * Used to add new features in XML database
     * add percent100
     */

    QFile file("userdata/version_0.2");
    if (file.exists()) {
        return true;
    }
    QDomNode n = docHistory.documentElement().firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement();
        if (!e.isNull()) {
            QString timeTotal = e.attribute("duration", "00:00:01");
            QString timeLeft = e.attribute("timeLeft", "00:00:01");
            int percent = completePercent(timeTotal, timeLeft);
            if (percent <= 100 && percent >= 0) {
                e.setAttribute("percent100", QString::number(percent));
            } else {
                e.setAttribute("percent100", "0");
            }
        }
        n = n.nextSibling();
    }

    n = docUser.documentElement().firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement();
        if (!e.isNull()) {
            QString timeTotal = e.attribute("duration", "00:00:01");
            QString timeLeft = e.attribute("timeLeft", "00:00:01");
            int percent = completePercent(timeTotal, timeLeft);
            if (percent <= 100 && percent >= 0) {
                e.setAttribute("percent100", QString::number(percent));
            } else {
                e.setAttribute("percent100", "0");
            }
        }
        n = n.nextSibling();
    }
    if (saveDocuments(k_tempFile, docHistory) && saveDocuments(k_userFile, docUser)) {
        if(file.open(QIODevice::WriteOnly)) {
            file.close();
            return true;
        }
        file.close();
    }
    return false;
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

    // Find last child node of root element
    QDomNode n = docHistory.documentElement().lastChild();
    QDomElement e = n.toElement();
    if (!e.isNull()) {
        if (toTimeDigital(e.attribute("timeLeft", ""), projectTime)) {
            projectName = e.attribute("name", "");
            return 0;
        }
    }

    return 1;
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

    if (fileName == k_tempFile) {
        // Simply append the new project
        QDomElement root = docHistory.documentElement();
        root.appendChild(nodeProject(docHistory, projectName, projectTime));
        if (!saveDocuments(k_tempFile, docHistory)) {
            return -1;
        }
    } else if(fileName == k_userFile) {
        // Append if there is no same projectName exists.
        QDomElement root = docUser.documentElement();
        if (dataExisted(root, projectName)) {
            return 1;
        } else {
            root.appendChild(nodeProject(docUser, projectName, projectTime));
        }
        if (!saveDocuments(k_userFile, docUser)) {
            return -1;
        }
    }
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
    newProject.setAttribute("timeLeft", projectTime);
    newProject.setAttribute("percent100", "0");

    QDateTime createDate;
    QString QCreateDate = createDate.currentDateTimeUtc().toString();
    QDomElement date = doc.createElement("createDate");
    QDomText tCreateDate = doc.createTextNode(QCreateDate);
    newProject.appendChild(date);
    date.appendChild(tCreateDate);

    return newProject;
}

void DataBase::updateCurrent(const QString &fileName, const QString &projectName, const QString &timeLeft)
{
    if (fileName == k_tempFile) {
        // Update the last project in tempplans.xml
        QDomNode n = docHistory.documentElement().lastChild();
        QDomElement e = n.toElement();
        if (!e.isNull() && e.attribute("name", "") == projectName) {
            e.setAttribute("timeLeft", timeLeft);
            int percentage = completePercent(e.attribute("duration", "00:00:01"), timeLeft);
            if (percentage <= 100 && percentage >=0) {
                e.setAttribute("percent100", QString::number(percentage));
            }
        }
    } else if (fileName == k_userFile){
        // Update the correspond project in userplans.xml
        QDomNode n = docUser.documentElement().firstChild();
        while (!n.isNull()) {
            QDomElement e = n.toElement();
            if (!e.isNull()) {
                if (e.attribute("name", "") == projectName) {
                    e.setAttribute("timeLeft", timeLeft);
                    break;
                }
            }
            n = n.nextSibling();
        }
    }
}

int DataBase::completePercent(const QString &timeTotal, const QString &timeLeft)
{
    /**
     * @brief timeTotalInSec calculates how much percentage completed
     * @return percentage * 100 in type int
     */
    int timeTotalInSec = inSeconds(timeTotal);
    int timeLeftInSec = inSeconds(timeLeft);
    int percent = (timeTotalInSec - timeLeftInSec) * 100 / timeTotalInSec;

    return percent;
}

int DataBase::inSeconds(const QString &timeQString)
{
    Time timeDig;
    toTimeDigital(timeQString, timeDig);
    int seconds = timeDig.hour * 3600 + timeDig.minute * 60 + timeDig.second;
    return seconds;
}

bool DataBase::moveToLast(const QString &fileName, const int ID)
{
    if (fileName == k_tempFile) {
        QDomNode node = docHistory.elementsByTagName("projects").at(ID);
        QDomNode nodeLast = docHistory.lastChild();
        nodeLast.parentNode().insertAfter(node, nodeLast);
        return true;
    } else if (fileName == k_userFile) {
        QDomNode node = docHistory.elementsByTagName("projects").at(ID);
        node.parentNode().removeChild(node);
        node.parentNode().appendChild(node);
        return true;
    }
    return false;
}

QString DataBase::timeElapsed(QString begin, QString end)
{
    Time beginDig, endDig, timeDig;
    QString time;
    toTimeDigital(begin, beginDig);
    toTimeDigital(end, endDig);
    int beginSec = beginDig.hour * 3600 + beginDig.minute * 60 + beginDig.second;
    int endSec = endDig.hour * 3600 + endDig.minute * 60 + endDig.second;
    if (endSec <= beginSec) {
        time = "00:00:00";
        return time;
    }
    int timeSec = endSec - beginSec;
    timeDig.hour = timeSec / 3600;
    timeDig.minute = (timeSec/60) % 60;
    timeDig.second = timeSec % 60;
    time = toTimeQString(timeDig);
    return time;
}

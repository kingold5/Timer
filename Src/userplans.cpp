#include <QMessageBox>
#include <QTableView>
#include <QProgressBar>
#include "userplans.h"
#include "ui_userplans.h"


// TODO:
// Recording every run's datetime, period.
// Show every run's detail in table view

UserPlans::UserPlans(DataBase *pdata, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPlans),
    data(pdata),
    docRef(pdata->getDocUser()),
    model(new UserProjectModel(docRef, this)),
    fileName(DataBase::k_userFile),
    showtimer(nullptr),
    newPlan(new uiSinglePlan(docRef, this)),
    needEdit(false)
{
    ui->setupUi(this);
    setWindowTitle("User Plans");
    ui->tableView->setModel(model);
    renderProgress();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->clearSelection();
    // newPlan->setAttribute(Qt::WA_DeleteOnClose);
    connect(newPlan, SIGNAL(sendData(const QString &, const QString &, const int &, const QString &, const QString &)),
            this, SLOT(submitData(const QString &, const QString &, const int &, const QString &, const QString &)));
    connect(this, SIGNAL(update(const QString &, const QString &, const int &, const QString &, const QString &)),
            newPlan, SLOT(updateData(const QString &, const QString &, const int &, const QString &, const QString &)));
}

UserPlans::~UserPlans()
{
    delete ui;
}

void UserPlans::renderProgress()
{
    int rowCount = ui->tableView->model()->rowCount();
    for (int i = 0; i < rowCount; ++i)
    {
        renderProgressByIdx(i);
    }
}

void UserPlans::renderProgressByIdx(int i)
{
    QModelIndex index = ui->tableView->model()->index(i, 4);
    QProgressBar *progress = new QProgressBar;
    progress->setMinimum(0);
    progress->setMaximum(100);
    progress->setValue(ui->tableView->model()->index(i, 4).data().toInt());
    progress->setAutoFillBackground(true);
    ui->tableView->setIndexWidget(index, progress);
}

void UserPlans::update(const QString &projectName, const QString &timeLeft)
{
    /***
     * Update timeLeft, percent100, progress bar and save XML file
     */

    data->updateCurrent(fileName, projectName, timeLeft);
    renderProgress();
    data->saveDataBase(fileName);
}

void UserPlans::submitData(const QString &planName, const QString &planTime,
                           const int &importance, const QString &planDeadline,
                           const QString &description)
{
    QDomElement root = docRef.documentElement();
    if (needEdit) {
        // TODO:
        // Use datachanged instead of layoutchanged
        needEdit = false;
        emit model->layoutAboutToBeChanged();
        editSinglePlan(planName, planTime, importance, planDeadline, description);
        newPlan->close();
        emit model->layoutChanged();
    } else if (!data->dataExisted(root, planName)) {
        emit model->layoutAboutToBeChanged();
        QDomElement project = DataBase::nodeProjectRich(docRef, planName, planTime, importance, planDeadline, description);
        docRef.documentElement().appendChild(project);
        emit model->layoutChanged();
        newPlan->close();
        renderProgressByIdx(ui->tableView->model()->rowCount() - 1);
    } else {
        QMessageBox::warning(this, "Warning", "Project already exists!");
    }
}

void UserPlans::editSinglePlan(const QString &planName, const QString &planTime,
                               const int &importance, const QString &planDeadline,
                               const QString &description)
{
    elementToEdit.setAttribute("name", planName);
    elementToEdit.setAttribute("duration", planTime);
    elementToEdit.firstChildElement("importance").firstChild().setNodeValue(QString::number(importance));
    elementToEdit.firstChildElement("description").firstChild().setNodeValue(description);
    elementToEdit.firstChildElement("deadline").firstChild().setNodeValue(planDeadline);
}

void UserPlans::on_pushButtonRun_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        QString projectName = ui->tableView->model()->index(index.row(), 0).data().toString();
        QString projectTime = ui->tableView->model()->index(index.row(), 3).data().toString();
        if (index.row() != ui->tableView->model()->rowCount()-1) {
            ui->tableView->model()->moveRows(QModelIndex(), index.row(), 1, QModelIndex(), ui->tableView->model()->rowCount());
        }
        showtimer = new ShowTimer(projectTime, projectName, this);
        connect(showtimer, SIGNAL(projectNeedsUpdate(const QString &, const QString &)),
                this, SLOT(update(const QString &, const QString &)));
        showtimer->setAttribute(Qt::WA_DeleteOnClose);
        showtimer->show();
    }
}

void UserPlans::on_pushButtonSave_clicked()
{
    if (!data->saveDataBase(fileName)) {
        QMessageBox::warning(this, "Warning", "Failed to save data!");
    }
    this->close();
}

void UserPlans::on_pushButtonCancel_clicked()
{
    if (!data->resetDataBase(fileName)) {
        QMessageBox::warning(this, "Warning", "Failed to load data!");
    }
    this->close();
}

void UserPlans::on_pushButtonDelete_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        ui->tableView->model()->removeRows(index.row(), 1);
    }
}

void UserPlans::on_pushButtonAdd_clicked()
{
    newPlan->clearData();
    newPlan->show();
}

void UserPlans::on_pushButtonEdit_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        needEdit = true;
        QDomNodeList nodes = docRef.elementsByTagName("projects");
        elementToEdit = nodes.at(index.row()).toElement();
        const QString planName = elementToEdit.attribute("name", "");
        const QString planTime = elementToEdit.attribute("duration", "");
        const QString planDeadline = elementToEdit.firstChildElement("deadline").text();
        const QString description = elementToEdit.firstChildElement("description").text();
        const int importance = elementToEdit.firstChildElement("importance").text().toInt();
        emit update(planName, planTime, importance, planDeadline, description);
        newPlan->show();
    }
}

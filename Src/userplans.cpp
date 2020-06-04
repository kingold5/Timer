#include <QMessageBox>
#include <QTableView>
#include <QProgressBar>
#include "userplans.h"
#include "ui_userplans.h"

UserPlans::UserPlans(DataBase *pdata, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPlans),
    data(pdata),
    docRef(pdata->getDocUser()),
    model(new UserProjectModel(docRef, this)),
    fileName(DataBase::k_userFile),
    showtimer(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("User Plans");
    ui->tableView->setModel(model);
    renderProgress();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnToContents(0);
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
        QModelIndex index = ui->tableView->model()->index(i, 3);
        QProgressBar *progress = new QProgressBar;
        progress->setMinimum(0);
        progress->setMaximum(100);
        progress->setValue(ui->tableView->model()->index(i, 3).data().toInt());
        progress->setAutoFillBackground(true);
        ui->tableView->setIndexWidget(index, progress);
    }
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

void UserPlans::on_pushButtonRun_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        QString projectName = ui->tableView->model()->index(index.row(), 0).data().toString();
        QString projectTime = ui->tableView->model()->index(index.row(), 2).data().toString();
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

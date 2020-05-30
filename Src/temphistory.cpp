#include <QMessageBox>
#include <QTableView>
#include "temphistory.h"
#include "ui_temphistory.h"

TempHistory::TempHistory(DataBase *pdata, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TempHistory),
    data(pdata),
    docRef(pdata->getDocHistory()),
    tempModel(new ProjectsModel(docRef, this)),
    fileName(DataBase::k_tempFile)
{
    ui->setupUi(this);
    ui->tableView->setModel(tempModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnToContents(0);
}

TempHistory::~TempHistory()
{
    delete tempModel;
    delete ui;
}

void TempHistory::update(const QString &projectName, const QString &timeLeft)
{
    data->saveDataBase(fileName);
}

void TempHistory::on_pushButtonRun_clicked()
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

void TempHistory::on_pushButtonSave_clicked()
{
    if (!data->saveDataBase(fileName)) {
        QMessageBox::warning(this, "Warning", "Failed to save data!");
    }
    this->close();
}

void TempHistory::on_pushButtonCancel_clicked()
{
    if (!data->resetDataBase(fileName)) {
        QMessageBox::warning(this, "Warning", "Failed to load data!");
    }
    this->close();
}

void TempHistory::on_pushButtonDelete_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        ui->tableView->model()->removeRows(index.row(), 1);
    }
}

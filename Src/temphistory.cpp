#include <QTableView>
#include "temphistory.h"
#include "projectsmodel.h"
#include "ui_temphistory.h"
#include "database.hpp"

TempHistory::TempHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TempHistory)
{
    ui->setupUi(this);
    file.setFileName(DataBase::k_tempFile);
    DataBase::loadDocuments(file, doc, QIODevice::ReadWrite);

    tempModel = new ProjectsModel(doc, this);
    ui->tableView->setModel(tempModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

TempHistory::~TempHistory()
{
    if (file.isOpen()) {
        QTextStream ts(&file);
        file.resize(0);
        ts<<doc.toString();
        file.close();
    }

    delete tempModel;
    delete ui;
}

void TempHistory::on_pushButtonRun_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        QString projectName = ui->tableView->model()->index(index.row(), 0).data().toString();
        QString projectTime = ui->tableView->model()->index(index.row(), 1).data().toString();

        showtimer = new ShowTimer(projectTime, projectName, this);
        showtimer->setAttribute(Qt::WA_DeleteOnClose);
        showtimer ->show();
    }
}

void TempHistory::on_pushButtonEdit_clicked()
{
    QTextStream ts(&file);
    file.resize(0);
    ts<<doc.toString();
    file.close();
    this->close();
}

void TempHistory::on_pushButtonCancel_clicked()
{
    file.close();
    this->close();
}

void TempHistory::on_pushButtonDelete_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        ui->tableView->model()->removeRows(index.row(), 1);
    }
}

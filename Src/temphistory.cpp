#include <QTableView>
#include "temphistory.h"
#include "projectsmodel.h"
#include "ui_temphistory.h"

TempHistory::TempHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TempHistory)
{
    ui->setupUi(this);
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << fileName + "failed to open in model";
    }
    if (!doc.setContent(&file)) {
        qDebug() << fileName + "failed to load in model";
        file.close();
    }

    tempModel = new ProjectsModel(doc, this);
    ui->tableView->setModel(tempModel);
    ui->tableView->setColumnWidth(2, 230);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
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

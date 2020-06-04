#include <QMessageBox>
#include <QDebug>
#include "mainWindow.h"
#include "myspinbox.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    showtimer(nullptr),
    history(nullptr),
    userPlans(nullptr),
    data(new DataBase)
{
    ui->setupUi(this);
    setWindowTitle("Timer");
    // Initialize directory and files
    if (!data->initDBFiles()) {
        QMessageBox::warning(this, "Warning", "Failed to create database!");
    }
    if (!data->updateDataBase()) {
        QMessageBox::warning(this, "Warning", "Failed to update database!");
    }
    setupProject();
}

MainWindow::~MainWindow()
{
    delete data;
    delete ui;
}

void MainWindow::setupProject()
{
    Time projectTime = {0, 0, 0};
    QString projectName="";

    data->loadTemp(projectName, projectTime);
    ui->planName->setText(projectName);
    ui->timeHour->setValue(projectTime.hour);
    ui->timeMin->setValue(projectTime.minute);
    ui->timeSec->setValue(projectTime.second);
    ui->timeHour->setRange(0, 99);
    ui->timeMin->setRange(0, 59);
    ui->timeSec->setRange(0, 59);
    ui->timeMin->setWrapping(true);
    ui->timeSec->setWrapping(true);
}

void MainWindow::updateHistory(const QString &projectName, const QString &timeLeft)
{
    data->updateCurrent(DataBase::k_tempFile, projectName, timeLeft);
    data->saveDataBase(DataBase::k_tempFile);
    setupProject();
}

void MainWindow::on_PushButtonRunNow_clicked()
{
    Time projectTime = {ui->timeHour->value(),
                        ui->timeMin->value(),
                        ui->timeSec->value()};
    data->append(DataBase::k_tempFile,
                 ui->planName->text(),
                 projectTime);

    showtimer = new ShowTimer(projectTime, ui->planName->text(), this);
    connect(showtimer, SIGNAL(projectNeedsUpdate(const QString &, const QString &)),
            this, SLOT(updateHistory(const QString &, const QString &)));
    showtimer->setAttribute(Qt::WA_DeleteOnClose);
    showtimer ->show();
}

void MainWindow::on_PushButtonAdd_clicked()
{
    Time projectTime = {ui->timeHour->value(),
                        ui->timeMin->value(),
                        ui->timeSec->value()};
    int result = data->append(DataBase::k_userFile,
                              ui->planName->text(),
                              projectTime);
    switch (result) {
    case -1: {
        // File operation failed
        QMessageBox::critical(this, "Failed", "File operation failed!");
        break;
    }
    case 1: {
        // Data exists
        QMessageBox::information(this, "Failed", "Project name exists, please input another one.");
        break;
    }
    default: {
        // Succeed
        QMessageBox::information(this, "Succeed", "Projects added!");
        break;
    }
    }
}

void MainWindow::on_actionHistory_triggered()
{
    history = new TempHistory(data, this);
    history->setAttribute(Qt::WA_DeleteOnClose);
    history->show();
}

void MainWindow::on_actionUser_Plans_triggered()
{
    userPlans = new UserPlans(data, this);
    userPlans->setAttribute(Qt::WA_DeleteOnClose);
    userPlans->show();
}

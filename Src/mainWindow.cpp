#include <QMessageBox>
#include "mainWindow.h"
#include "ui_mainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    data(new DataBase)
{
    ui->setupUi(this);
    setWindowTitle("Timer");
    setupProject();
}

MainWindow::~MainWindow()
{
    delete data;
    delete ui;
}

void MainWindow::setupProject()
{
    Time projectTime = {0.0, 0.0, 0.0};
    QString projectName="";

    data->loadTemp(projectName, projectTime);
    ui->planName->setText(projectName);
    ui->timeHour->setValue(projectTime.hour);
    ui->timeMin->setValue(projectTime.minute);
    ui->timeSec->setValue(projectTime.second);
}

void MainWindow::on_PushButtonRunNow_clicked()
{
    Time projectTime = {ui->timeHour->value(),
                        ui->timeMin->value(),
                        ui->timeSec->value()};
    data->append("tempplans.xml",
                 ui->planName->text(),
                 projectTime);

    showtimer = new ShowTimer(projectTime, ui->planName->text(), this);
    connect(showtimer, SIGNAL(projectChanged()),
            this, SLOT(setupProject()));
    showtimer->setAttribute(Qt::WA_DeleteOnClose);
    showtimer ->show();
}

void MainWindow::on_PushButtonAdd_clicked()
{
    Time projectTime = {ui->timeHour->value(),
                        ui->timeMin->value(),
                        ui->timeSec->value()};
    int result = data->append("userplans.xml",
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
    history = new TempHistory(this);
    history->setAttribute(Qt::WA_DeleteOnClose);
    history->show();
}

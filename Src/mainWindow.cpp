#include <QMessageBox>
#include "mainWindow.h"
#include "ui_mainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    time(new CountDown),
    data(new DataBase)
{
    ui->setupUi(this);
    setWindowTitle("Timer");
    // Guess vector will take 20 projects
    addedProjects.reserve(30000);
    tempProjects.reserve(30000);
    data->loadAll("tempplans.xml", tempProjects);

    Time projectTime;
    QString projectName="";
    data->loadTemp(projectName, projectTime);
    ui->planName->setText(projectName);
    ui->timeHour->setValue(projectTime.hour);
    ui->timeMin->setValue(projectTime.minute);
    ui->timeSec->setValue(projectTime.second);
}

MainWindow::~MainWindow()
{
    delete data;
    delete time;
    delete ui;
}

void MainWindow::on_PushButtonOK_clicked()
{
    Time projectTime = {ui->timeHour->value(),
                        ui->timeMin->value(),
                        ui->timeSec->value()};
    time->setTimer(projectTime);
    data->append("tempplans.xml",
                 ui->planName->text(),
                 projectTime);

    showtimer = new ShowTimer(time, ui->planName->text(), this);
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

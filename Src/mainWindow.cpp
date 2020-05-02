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
    double hour=0.0, min=0.0, sec=0.0;
    QString projectName="";
    data->loadTemp(&projectName, &hour, &min, &sec);
    ui->planName->setText(projectName);
    ui->timeHour->setValue(hour);
    ui->timeMin->setValue(min);
    ui->timeSec->setValue(sec);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PushButtonOK_clicked()
{
    time->setTimer(ui->timeHour->value(),
                   ui->timeMin->value(),
                   ui->timeSec->value());
    // data->setProject(ui->planName->text(), time->timeQString());
    data->appendTemp(ui->planName->text(), time->timeQString());

    showtimer = new ShowTimer(time, ui->planName->text(), this);
    showtimer ->show();
}

void MainWindow::on_PushButtonAdd_clicked()
{
    int result = data->append(ui->planName->text(),
                              ui->timeHour->value(),
                              ui->timeMin->value(),
                              ui->timeSec->value());
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

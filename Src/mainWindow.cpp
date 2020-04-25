#include "mainWindow.h"
#include "ui_mainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    time(new CountDown)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PushButtonOK_clicked()
{
    time->setTimer(static_cast<int>(ui->timeHour->value()),
                   static_cast<int>(ui->timeMin->value()),
                   static_cast<int>(ui->timeSec->value()));
    showtimer = new ShowTimer(this, time);
    showtimer ->show();
}

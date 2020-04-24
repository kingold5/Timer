#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "Countdown.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new Countdown)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PushButtonOK_clicked()
{
    timer->setTimer(static_cast<int>(ui->timeHour->value()), static_cast<int>(ui->timeMin->value()),\
                    static_cast<int>(ui->timeSec->value()));

}

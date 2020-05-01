#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Countdown.hpp"
#include "showtimer.h"
#include "database.hpp"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_PushButtonOK_clicked();

    void on_PushButtonAdd_clicked();

private:
    Ui::MainWindow *ui;
    CountDown* time;
    ShowTimer* showtimer;
    DataBase* data;
};

#endif // MAINWINDOW_H

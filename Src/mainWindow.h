#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Countdown.hpp"
#include "showtimer.h"
#include "database.hpp"
#include "projectsstruct.h"


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
    QVector<Projects> addedProjects;
    QVector<Projects> tempProjects;
};

#endif // MAINWINDOW_H

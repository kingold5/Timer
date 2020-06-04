#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "showtimer.h"
#include "temphistory.h"
#include "userplans.h"
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
    void on_PushButtonRunNow_clicked();
    void on_PushButtonAdd_clicked();
    void on_actionHistory_triggered();

    void updateHistory(const QString &projectName, const QString &timeLeft);
    void setupProject();

    void on_actionUser_Plans_triggered();

private:
    Ui::MainWindow *ui;
    ShowTimer* showtimer;
    TempHistory *history;
    UserPlans *userPlans;
    DataBase* data;
};

#endif // MAINWINDOW_H

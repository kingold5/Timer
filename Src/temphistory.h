#ifndef TEMPHISTORY_H
#define TEMPHISTORY_H

#include <QDialog>
#include <QTableView>
#include <QDomDocument>
#include "projectsmodel.h"
#include "showtimer.h"
#include "database.hpp"

namespace Ui {
class TempHistory;
}

class TempHistory : public QDialog
{
    Q_OBJECT

public:
    explicit TempHistory(DataBase *pdata, QWidget *parent = nullptr);
    ~TempHistory();

private slots:
    void on_pushButtonRun_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();
    // void updateHistory(const QString &projectName, const QString &timeLeft);

private:
    Ui::TempHistory *ui;
    DataBase *data;
    QDomDocument docRef;
    ProjectsModel *tempModel;
    QString fileName;
    ShowTimer *showtimer;
};

#endif // TEMPHISTORY_H

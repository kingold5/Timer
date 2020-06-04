#ifndef USERPLANS_H
#define USERPLANS_H

#include <QDialog>
#include <QTableView>
#include <QDomDocument>
#include "userprojectmodel.h"
#include "showtimer.h"
#include "database.hpp"

namespace Ui {
class UserPlans;
}

class UserPlans : public QDialog
{
    Q_OBJECT

public:
    explicit UserPlans(DataBase *pdata, QWidget *parent = nullptr);
    ~UserPlans();

public slots:
    void on_pushButtonRun_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonDelete_clicked();
    void update(const QString &projectName, const QString &timeLeft);
    void renderProgress();

private:
    Ui::UserPlans *ui;
protected:
    DataBase *data;
    QDomDocument docRef;
    UserProjectModel *model;
    QString fileName;
    ShowTimer *showtimer;
};

#endif // USERPLANS_H

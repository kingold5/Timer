#ifndef USERPLANS_H
#define USERPLANS_H

#include <QDialog>
#include <QTableView>
#include <QDomDocument>
#include "userprojectmodel.h"
#include "showtimer.h"
#include "uisingleplan.h"
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
    void renderProgressByIdx(int i);

signals:
    void update(const QString &planName, const QString &planTime,
                const int &importance, const QString &planDeadline,
                const QString &description);

private:
    Ui::UserPlans *ui;
    DataBase *data;
    QDomDocument docRef;
    UserProjectModel *model;
    QString fileName;
    ShowTimer *showtimer;
    uiSinglePlan *newPlan;
    bool needEdit;
    QDomElement elementToEdit;

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonEdit_clicked();
    void submitData(const QString &planName, const QString &planTime,
                    const int &importance, const QString &planDeadline,
                    const QString &description);
    void editSinglePlan(const QString &planName, const QString &planTime,
                        const int &importance, const QString &planDeadline,
                        const QString &description);
};

#endif // USERPLANS_H

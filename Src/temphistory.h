#ifndef TEMPHISTORY_H
#define TEMPHISTORY_H

#include <QWidget>
#include <QTableView>
#include <QDomDocument>
#include "projectsmodel.h"
#include "showtimer.h"

namespace Ui {
class TempHistory;
}

class TempHistory : public QWidget
{
    Q_OBJECT

public:
    explicit TempHistory(QWidget *parent = nullptr);
    ~TempHistory();

private slots:
    void on_pushButtonRun_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonDelete_clicked();

private:
    Ui::TempHistory *ui;
    QString fileName = "tempplans.xml";
    QFile file;
    QDomDocument doc;
    ProjectsModel *tempModel;
    ShowTimer *showtimer;
};

#endif // TEMPHISTORY_H

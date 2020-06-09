#ifndef ADDPLAN_H
#define ADDPLAN_H

#include <QDialog>
#include <QDomDocument>

namespace Ui {
class AddPlan;
}

class AddPlan : public QDialog
{
    Q_OBJECT

public:
    explicit AddPlan(QDomDocument &doc, QWidget *parent = nullptr);
    ~AddPlan();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddPlan *ui;
    QDomDocument docRef;
};

#endif // ADDPLAN_H

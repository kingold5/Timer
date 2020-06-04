#ifndef ADDPLAN_H
#define ADDPLAN_H

#include <QDialog>

namespace Ui {
class AddPlan;
}

class AddPlan : public QDialog
{
    Q_OBJECT

public:
    explicit AddPlan(QWidget *parent = nullptr);
    ~AddPlan();

private:
    Ui::AddPlan *ui;
};

#endif // ADDPLAN_H

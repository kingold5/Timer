#include "addplan.h"
#include "ui_addplan.h"

AddPlan::AddPlan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPlan)
{
    ui->setupUi(this);
}

AddPlan::~AddPlan()
{
    delete ui;
}

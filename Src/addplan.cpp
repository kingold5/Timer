#include "addplan.h"
#include "ui_addplan.h"
#include "myspinbox.h"

AddPlan::AddPlan(QDomDocument doc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPlan),
    docRef(doc)
{
    ui->setupUi(this);
    ui->mySpinBoxHour->setRange(0, 99);
    ui->mySpinBoxMin->setRange(0, 59);
    ui->mySpinBoxSec->setRange(0, 59);
    ui->mySpinBoxHour->setWrapping(true);
    ui->mySpinBoxMin->setWrapping(true);
    ui->mySpinBoxSec->setWrapping(true);

}

AddPlan::~AddPlan()
{
    delete ui;
}

#include <QDebug>
#include "addplan.h"
#include "ui_addplan.h"
#include "myspinbox.h"
#include "projectsstruct.h"

AddPlan::AddPlan(QDomDocument doc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPlan),
    docRef(doc)
{
    ui->setupUi(this);
    // Set spin box
    ui->mySpinBoxHour->setRange(0, 99);
    ui->mySpinBoxMin->setRange(0, 59);
    ui->mySpinBoxSec->setRange(0, 59);
    ui->mySpinBoxHour->setWrapping(true);
    ui->mySpinBoxMin->setWrapping(true);
    ui->mySpinBoxSec->setWrapping(true);

    // Set combobox
    ui->comboBoxImportance->addItem("<Default>");
    ui->comboBoxImportance->addItem(QIcon(":/icons/Rcs/single_star.png"), "Normal");
    ui->comboBoxImportance->addItem(QIcon(":/icons/Rcs/double_stars.png"), "Important");
    ui->comboBoxImportance->addItem(QIcon(":/icons/Rcs/triple_stars.png"), "Urgent");
    ui->comboBoxImportance->setIconSize(QSize(54, 18));

    // Calendar
    ui->dateTimeEditDeadline->setCalendarPopup(true);
    ui->dateTimeEditDeadline->setMinimumDateTime(QDateTime::currentDateTimeUtc());
    ui->dateTimeEditDeadline->setDisplayFormat("dd.MMMM.yyyy hh:mm:ss");

    ui->plainTextEditDescription->setPlaceholderText("Plan Summary");
}

AddPlan::~AddPlan()
{
    delete ui;
}

void AddPlan::on_buttonBox_accepted()
{
    Time duration = {ui->mySpinBoxHour->value(),
                     ui->mySpinBoxMin->value(),
                     ui->mySpinBoxSec->value()};
    int index = ui->comboBoxImportance->currentIndex();
    QString deadline = ui->dateTimeEditDeadline->dateTime().toString();
    QString description = ui->plainTextEditDescription->document()->toPlainText();
    // TODO:
    // Add nodeproject() to record child node index and deadline
}

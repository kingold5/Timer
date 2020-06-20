#include <QDebug>
#include "uisingleplan.h"
#include "myspinbox.h"
#include "projectsstruct.h"
#include "database.hpp"
#include "ui_uisingleplan.h"

uiSinglePlan::uiSinglePlan(QDomDocument &doc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uiSinglePlan),
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
    ui->dateTimeEditDeadline->setDisplayFormat("dd.MMMM.yyyy hh:mm:ss");

    ui->plainTextEditDescription->setPlaceholderText("Plan Summary");
}

uiSinglePlan::~uiSinglePlan()
{
    delete ui;
}

void uiSinglePlan::clearData()
{
    ui->lineEditPlanName->clear();
    ui->mySpinBoxHour->setValue(0);
    ui->mySpinBoxMin->setValue(0);
    ui->mySpinBoxSec->setValue(0);
    ui->comboBoxImportance->setCurrentIndex(0);
    ui->dateTimeEditDeadline->setMinimumDateTime(QDateTime::currentDateTime());
    ui->plainTextEditDescription->clear();

}

void uiSinglePlan::updateData(const QString &planName, const QString &planTime,
                              const int &importance, const QString &planDeadline,
                              const QString &description)
{
    ui->lineEditPlanName->setText(planName);
    Time duration;
    DataBase::toTimeDigital(planTime, duration);
    ui->mySpinBoxHour->setValue(duration.hour);
    ui->mySpinBoxMin->setValue(duration.minute);
    ui->mySpinBoxSec->setValue(duration.second);
    // Convert time from UTC to local time
    ui->dateTimeEditDeadline->clearMinimumDateTime();
    QDateTime date = QDateTime::fromString(planDeadline);
    date.setTimeSpec(Qt::UTC);
    ui->dateTimeEditDeadline->setDateTime(date.toLocalTime());
    ui->plainTextEditDescription->setPlainText(description);
    ui->comboBoxImportance->setCurrentIndex(importance);
}

void uiSinglePlan::on_buttonBox_accepted()
{
    QString planName = ui->lineEditPlanName->text();
    Time duration = {ui->mySpinBoxHour->value(),
                     ui->mySpinBoxMin->value(),
                     ui->mySpinBoxSec->value()};
    QString planTime = DataBase::toTimeQString(duration);
    QString planDeadline = ui->dateTimeEditDeadline->dateTime().toUTC().toString();
    QString description = ui->plainTextEditDescription->document()->toPlainText();
    int importance = ui->comboBoxImportance->currentIndex();
    emit sendData(planName, planTime, importance, planDeadline, description);
}

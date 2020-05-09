#include "temphistory.h"
#include "ui_temphistory.h"

temphistory::temphistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::temphistory)
{
    ui->setupUi(this);
}

temphistory::~temphistory()
{
    delete ui;
}

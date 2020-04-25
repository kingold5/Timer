#include "showtimer.h"
#include "ui_showtimer.h"
#include <QString>
#include <QLCDNumber>

ShowTimer::ShowTimer(QWidget *parent, CountDown* ptime) :
    QDialog(parent),
    ui(new Ui::ShowTimer),
    time(ptime),
    timer(new QTimer(this))
{
    ui->setupUi(this);
    ui->lcdTimer->setSegmentStyle(QLCDNumber::Filled);
    // ui->lcdTimer->display("00:00:00");
    connect(timer, SIGNAL(timeout()), this, SLOT(display()));

    //connect(this, I)
    timer->start(1000);
}

ShowTimer::~ShowTimer()
{
    delete ui;
    delete timer;
}

void ShowTimer::display()
{
    time->timeDec(1);
    QString text = time->getQString();
    ui->lcdTimer->display(text);
}

void ShowTimer::reject() {
    if (timer->isActive() == true) {
        timer->stop();
    }
    QDialog::reject();
}

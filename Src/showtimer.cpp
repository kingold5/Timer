#include "showtimer.h"
#include "ui_showtimer.h"
#include <QString>
#include <QLCDNumber>


ShowTimer::ShowTimer(QWidget *parent, CountDown* ptime) :
    QDialog(parent),
    ui(new Ui::ShowTimer),
    time(ptime),
    timer(new QTimer(this)),
    text(ptime->getQString()),
    efx(new QSoundEffect(this))
{
    ui->setupUi(this);
    ui->lcdTimer->setSegmentStyle(QLCDNumber::Filled);
    ui->lcdTimer->display(text);
    ui->pushButtonStop->setEnabled(false);
    // ui->lcdTimer->display("00:00:00");
    connect(timer, SIGNAL(timeout()), this, SLOT(display()));
    timer->start(1000);

    efx->setSource(QUrl("qrc:/sounds/Rcs/analog-watch-alarm_daniel-simion.wav"));
    efx->setVolume(0.5f);
    efx->setLoopCount(6);
}

ShowTimer::~ShowTimer()
{
    delete ui;
}

void ShowTimer::display()
{
    if(time->timeDec(1) == 1) {
        timer->stop();
        alarm();
    }
    QString text = time->getQString();
    ui->lcdTimer->display(text);
}

void ShowTimer::reject() {
    if (timer->isActive() == true) {
        timer->stop();
    }
    if (efx->isPlaying() == true) {
        efx->stop();
    }
    QDialog::reject();
}

void ShowTimer::alarm() {
    efx->play();
    ui->pushButtonStop->setEnabled(true);
}

void ShowTimer::on_pushButtonStop_clicked()
{
    efx->stop();
}

#include <QString>
#include <QLCDNumber>
#include "showtimer.h"
#include "ui_showtimer.h"


ShowTimer::ShowTimer(CountDown* ptime, const QString &name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowTimer),
    time(ptime),
    timer(new QTimer(this)),
    textTime(ptime->timeQString()),
    efx(new QSoundEffect(this))
{
    ui->setupUi(this);
    setWindowTitle("Project");
    ui->lcdTimer->setSegmentStyle(QLCDNumber::Filled);
    ui->lcdTimer->display(textTime);
    ui->pushButtonStop->setEnabled(false);
    ui->labelProName->setText(name);
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
        ui->pushButtonPause->setEnabled(false);
        alarm();
    }
    QString textTime = time->timeQString();
    ui->lcdTimer->display(textTime);
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

void ShowTimer::on_pushButtonPause_clicked()
{
    QString pause = "Pause Clock";
    QString start = "Start Clock";
    if (ui->pushButtonPause->text() == pause) {
        timer->stop();
        ui->pushButtonPause->setText(start);
    } else {
        timer->start(1000);
        ui->pushButtonPause->setText(pause);
    }
}

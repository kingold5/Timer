#ifndef SHOWTIMER_H
#define SHOWTIMER_H

#include <QDialog>
#include <QTimer>
#include <QSoundEffect>
#include "Countdown.hpp"

namespace Ui {
class ShowTimer;
}

class ShowTimer : public QDialog
{
    Q_OBJECT

public:
    explicit ShowTimer(QWidget* parent = 0, CountDown* ptime=0, const QString name=QString(""));
    ~ShowTimer();

public slots:
    void reject();

private slots:
    void display();

    void on_pushButtonStop_clicked();

private:
    void alarm();

    Ui::ShowTimer *ui;
    CountDown* time;
    QTimer* timer;
    QString textTime;
    QSoundEffect* efx;
};

#endif // SHOWTIMER_H

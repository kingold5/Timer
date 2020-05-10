#ifndef SHOWTIMER_H
#define SHOWTIMER_H

#include <QDialog>
#include <QTimer>
#include <QSoundEffect>
#include "Countdown.hpp"
#include "projectsstruct.h"

namespace Ui {
class ShowTimer;
}

class ShowTimer : public QDialog
{
    Q_OBJECT

public:
    explicit ShowTimer(const Time &timeDigital, const QString& name, QWidget* parent = 0);
    explicit ShowTimer(const QString &timeQString, const QString& name, QWidget* parent = 0);
    ~ShowTimer();

protected:
    void constructor(const QString &name);

public slots:
    void reject();

private slots:
    void display();
    void on_pushButtonStop_clicked();
    void on_pushButtonPause_clicked();

private:
    void alarm();

    Ui::ShowTimer *ui;
    CountDown* time;
    QTimer* timer;
    QString textTime;
    QSoundEffect* efx;
};

#endif // SHOWTIMER_H

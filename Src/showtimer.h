#ifndef SHOWTIMER_H
#define SHOWTIMER_H

#include <QDialog>
#include <QTimer>
#include "Countdown.hpp"

namespace Ui {
class ShowTimer;
}

class ShowTimer : public QDialog
{
    Q_OBJECT

public:
    explicit ShowTimer(QWidget* parent = 0, CountDown* ptime=0);
    ~ShowTimer();

public slots:
    void reject();

private slots:
    void display();

private:
    Ui::ShowTimer *ui;
    CountDown* time;
    QTimer* timer;
};

#endif // SHOWTIMER_H

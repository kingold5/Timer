#include "Countdown.hpp"
#include "database.hpp"

CountDown::CountDown(int h, int m, int s) :
    hour(h),
    minute(m),
    second(s)
{
    toSec();
}

CountDown::CountDown(const Time &time) :
    hour(time.hour),
    minute(time.minute),
    second(time.second)
{
    toSec();
}

CountDown::CountDown(const QString &time)
{
    Time timedigital;
    DataBase::toTimeDigital(time, timedigital);
    hour = timedigital.hour;
    minute = timedigital.minute;
    second = timedigital.second;
    toSec();
}

void CountDown::setTimer(const Time &time) {
    hour = time.hour;
    minute = time.minute;
    second = time.second;
    toSec();
}

void CountDown::getTimer(int *h, int *m, int *s) const {
    *h = hour;
    *m = minute;
    *s = second;
}

void CountDown::getTimer(Time &time) const {
    time.hour = hour;
    time.minute = minute;
    time.second = second;
}

QString CountDown::timeQString() const {
    QString time = QString("%1:%2:%3")
            .arg(hour, 2, 10, QChar('0'))
            .arg(minute, 2, 10, QChar('0'))
            .arg(second, 2, 10, QChar('0'));
    return time;
}

void CountDown::toNormal() {
    hour = numSeconds / 3600;
    minute = (numSeconds/60) % 60;
    second = numSeconds % 60;
}

void CountDown::toSec() {
    numSeconds = 3600*hour + 60*minute + second;
}

int CountDown::timeDec(int dec) {
    numSeconds -= dec;
    if (numSeconds < 0) {
        numSeconds = 0;
        toNormal();
        return 1;
    } else {
        toNormal();
        return 0;
    }
}

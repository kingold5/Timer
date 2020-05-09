#include "Countdown.hpp"

CountDown::CountDown(double h, double m, double s) :
    hour(static_cast<int>(h)),
    minute(static_cast<int>(m)),
    second(static_cast<int>(s))
{
    toSec();
}

void CountDown::setTimer(const Time &time) {
    hour = static_cast<int>(time.hour);
    minute = static_cast<int>(time.minute);
    second = static_cast<int>(time.second);
    toSec();
}

void CountDown::getTimer(int *h, int *m, int *s) const {
    *h = hour;
    *m = minute;
    *s = second;
}

void CountDown::getTimer(Time &time) const {
    time.hour = static_cast<double>(hour);
    time.minute = static_cast<double>(minute);
    time.second = static_cast<double>(second);
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

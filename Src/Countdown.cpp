#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "Countdown.hpp"

using namespace std;

CountDown::CountDown(int h, int m, int s) :
    hour(h), minute(m), second(s) {
    toSec();
}

void CountDown::setTimer(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
    toSec();
}

void CountDown::getTimer(int *h, int *m, int *s) {
    *h = hour;
    *m = minute;
    *s = second;
}

QString CountDown::timeQString() {
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

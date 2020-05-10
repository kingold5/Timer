#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QString>
#include "projectsstruct.h"

class CountDown {
    public:
        CountDown(double h=0.0, double m=0.0, double s=0.0);
        CountDown(const Time &time);
        CountDown(const QString &time);

        void setTimer(const Time &time);
        void getTimer(int* h, int* m, int* s) const;
        void getTimer(Time &time) const;
        QString timeQString() const;
        int timeDec(int dec);

    private:
        void toNormal();
        void toSec();

        int hour, minute, second;
        int numSeconds;
};


#endif

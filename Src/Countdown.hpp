#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QString>


class CountDown {
    public:
        CountDown(double h=0.0, double m=0.0, double s=0.0);

        void setTimer(int h, int m, int s);
        void setTimer(double h, double m, double s);
        void getTimer(int* h, int* m, int* s) const;
        QString timeQString() const;
        int timeDec(int dec);

    private:
        void toNormal();
        void toSec();

        int hour, minute, second;
        int numSeconds;
};


#endif

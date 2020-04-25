#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QString>


class CountDown {
    public:
        CountDown(int h=0, int m=0, int s=0);

        void setTimer(int h, int m, int s);
        void getTimer(int* h, int* m, int* s);
        QString getQString();
        int timeDec(int dec);

    private:
        void toNormal();
        void toSec();

        int hour, minute, second;
        int numSeconds;
};


#endif

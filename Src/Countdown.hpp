#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace std;


class Countdown {
    public:
        Countdown(int h=0, int m=0, int s=0);

        void setTimer(int h, int m, int s);
        void getTimer(int* h, int* m, int* s);
        void display();
        int timeDec();
        void run();

    private:
        int hour, minute, second;
};


#endif

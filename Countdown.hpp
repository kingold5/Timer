#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace std;


class Countdown {
    public:
        Countdown(int h, int m, int s);

        int hour, minute, second;
        void display();
        int timeDec();
        void run();
};

Countdown::Countdown(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
}

void Countdown::display() {
    system("clear");
    cout << "\r";
    cout << setfill('0') << setw(2) << hour << ":";
    cout << setfill('0') << setw(2) << minute << ":";
    cout << setfill('0') << setw(2) << second;
    cout << flush;
}

int Countdown::timeDec() {
    while(true) {
        Countdown::display();
        sleep(1);
        if (second == 0) {
            second = 59;
            if (minute == 0) {
                minute = 59;
                if (hour == 0) {
                    return 0;
                }
                else {
                    hour--;
                }
            }
            else {
                minute--;
            }
        }
        else {
                second--;
        }
    }
}

void Countdown::run() {
    if (Countdown::timeDec() == 0) {
        cout << '\a' << endl;
        cout << "Time countdown is finished!" << endl;
    }
}

#endif

#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace std;

void input(int* hour, int* minute, int* second) {
    cout << "Please input your time in hour" << endl;
    cin >> *hour;
    cout << "Please input your time in minute" << endl;
    cin >> *minute;
    cout << "Please input your time in second" << endl;
    cin >> *second;

}

void display(int hour, int minute, int second) {
    system("clear");
    cout << "\r";
    cout << setfill('0') << setw(2) << hour << ":";
    cout << setfill('0') << setw(2) << minute << ":";
    cout << setfill('0') << setw(2) << second;
    cout << flush;
}

void countdown(int* hour, int* minute, int* second) {
    while(true) {
        display(*hour, *minute, *second);
        sleep(1);
        if (*second == 0) {
            *second = 59;
            if (*minute == 0) {
                *minute = 59;
                if (*hour == 0) {
                    break;
                }
                else {
                    (*hour)--;
                }
            }
            else {
                (*minute)--;
            }
        }
        else {
                (*second)--;
        }
    }
}

int main() {
    int hour, minute, second;
    input(&hour, &minute, &second);
    countdown(&hour, &minute, &second);
    cout << '\a' << endl;
    cout << "Countdown finished" << endl;

    return 0;
}


#include <iostream>
#include "Countdown.hpp"

using namespace std;


int main() {
    int hour, minute, second;
    cout << "Please input hour:" << endl;
    cin >> hour;
    cout << "Please input minute:" << endl;
    cin >> minute;
    cout << "Please input second:" << endl;
    cin >> second;

    Countdown timer(hour, minute, second);
    timer.run();

    return 0;
}

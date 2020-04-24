#include <iostream>
#include <QApplication>
#include "mainWindow.h"

using namespace std;


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();

    /*
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
    */
}

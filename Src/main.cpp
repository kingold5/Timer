#include <iostream>
#include <QApplication>
#include <QFontDatabase>
#include "mainWindow.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    int id = QFontDatabase::addApplicationFont("../Ubuntu/Ubuntu-R.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family, 12);
    app.setFont(font);

    MainWindow w;
    w.show();

    return app.exec();
}

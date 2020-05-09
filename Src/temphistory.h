#ifndef TEMPHISTORY_H
#define TEMPHISTORY_H

#include <QWidget>

namespace Ui {
class temphistory;
}

class temphistory : public QWidget
{
    Q_OBJECT

public:
    explicit temphistory(QWidget *parent = nullptr);
    ~temphistory();

private:
    Ui::temphistory *ui;
};

#endif // TEMPHISTORY_H

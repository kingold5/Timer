#include "myspinbox.h"

MySpinBox::MySpinBox(QWidget *parent) : QSpinBox(parent)
{

}

QString MySpinBox::textFromValue(int val) const
{
    return QString("%1").arg(val, 2, 10, QChar('0'));
}

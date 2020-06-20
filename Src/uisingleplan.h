#ifndef ADDPLAN_H
#define ADDPLAN_H

#include <QDialog>
#include <QAbstractItemModel>
#include <QDomDocument>

namespace Ui {
class uiSinglePlan;
}

class uiSinglePlan : public QDialog
{
    Q_OBJECT

public:
    explicit uiSinglePlan(QDomDocument &doc, QWidget *parent = nullptr);
    ~uiSinglePlan();
    void clearData();

    Ui::uiSinglePlan *ui;

signals:
    void sendData(const QString &planName, const QString &planTime, const int &importance, const QString &planDeadline, const QString &description);

private slots:
    void on_buttonBox_accepted();
    void updateData(const QString &planName, const QString &planTime,
                    const int &importance, const QString &planDeadline,
                    const QString &description);

private:
    QDomDocument docRef;
};

#endif // ADDPLAN_H

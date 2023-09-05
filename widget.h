#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:
    Server *serverInstance;
    Ui::Widget *ui;
    QLCDNumber *lcdNumber_usercount;

private slots:
    void updateClientCount(int count);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H

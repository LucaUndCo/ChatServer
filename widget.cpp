#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    serverInstance = new Server(this);
    lcdNumber_usercount = ui->lcdNumber_usercount;
    lcdNumber_usercount->display(0);
    connect(serverInstance, &Server::clientCountUpdated, this, &Widget::updateClientCount);
}

Widget::~Widget()
{
    delete ui;

}


void Widget::updateClientCount(int count)
{
    if(lcdNumber_usercount) lcdNumber_usercount->display(count);
}

#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include "server.h"
class Client : public QObject{
    Q_OBJECT
private:
    QPointer<QTcpSocket> socket;
    Server *server;
    bool allchat = false;
    QString name;
public:
    Client(QTcpSocket *mySocket, Server *myServer);
    QTcpSocket *getSocket() const {return socket;}
    QString getName() const {return name;}

public slots:
    void readyRead();
    void closedClientConnection();
};
#endif // CLIENT_H

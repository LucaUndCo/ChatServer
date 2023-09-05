#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QObject>

class Client;

class Server : public QObject
{
    Q_OBJECT
private:
    QTcpServer          *server = nullptr;      // Server
    QVarLengthArray<QPointer<Client> > clients;
    int clientcount;

public:
    explicit Server(QObject *parent = nullptr);
signals:
    void clientCountUpdated(int count);
public slots:
    void removeClient(Client *client);
    void newClientConnection();             // Neue Verbindungsanfrage bearbeiten
    void sendMessageToAllClients(const QByteArray &messageData, QTcpSocket *senderSocket, QString clientName);
};




#endif // SERVER_H

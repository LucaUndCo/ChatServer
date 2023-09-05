#include "server.h"
#include "client.h"


Server::Server(QObject *parent) : QObject(parent)
{
    server = new QTcpServer;                    // Server erstellen
    server->listen(QHostAddress::Any, 6969);   // Server lauscht auf Clients auf port 6969
    connect(server, SIGNAL(newConnection()), this, SLOT(newClientConnection()));
    clients.resize(100);
    qDebug() << "server running";
}


void Server::removeClient(Client *client)
{
    for (int i = 0; i < clients.size(); ++i) {
        if (clients[i].data() == client) {
            clients.remove(i);
            clientcount --;
            emit clientCountUpdated(clientcount);
            return; // Exit the loop after removal
        }
    }
}


void Server::newClientConnection()
{
    qDebug() << "client connecting";
    QTcpSocket *newSocket = server->nextPendingConnection();

    int emptySlotIndex = -1;

    for(int i = 0; i < clients.size(); i++) {
        if(clients[i].isNull()) {
            emptySlotIndex = i;
            break;
        }
    }

    if (emptySlotIndex != -1) {
        clients[emptySlotIndex] = new Client(newSocket, this);
        clientcount ++;
        emit clientCountUpdated(clientcount);
        qDebug() << "client connected";
    } else {
        newSocket->write("Connection not possible, the server has reached its maximum capacity!\r\n");
        newSocket->disconnectFromHost();
        delete newSocket;
        qDebug() << "client cant connect";
    }
}

void Server::sendMessageToAllClients(const QByteArray &messageData, QTcpSocket *senderSocket, QString clientName)
{
    qDebug() << "function for sending messages started";
    if(messageData.contains("#")) return;
    for (Client *client : clients) {
        if(client != nullptr){
            if (client->getSocket() != senderSocket) {
                qDebug() << "client to send to found";
                QByteArray message;
                if(!clientName.isEmpty()){
                    message.append(clientName.toStdString());
                    message.append(": ");
                }
                message.append(messageData);
                client->getSocket()->write(message);
                message.clear();
                qDebug() << "message sent to client: " + messageData;
            }
        }

    }
}





#include "client.h"
#include "server.h"

Client::Client(QTcpSocket *mySocket, Server *myServer) : QObject(mySocket), server(myServer){
    socket = mySocket;
    socket->write("Welcome!\r\n");
    socket->write("please enter your username using #name and typing your name\r\n");
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(closedClientConnection()));

}

void Client::readyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    qDebug() << clientSocket;
        while (clientSocket->canReadLine())
        {
            QByteArray data = clientSocket->readLine();
            qDebug() << data;
            if(data=="#exit\r\n") closedClientConnection();
            if(data=="#allchat\r\n" && allchat == false)
            {
                allchat = true;
            }
            else if(data=="#allchat\r\n" && allchat == true)
            {
                allchat = false;
            }
            if(allchat == true && !data.contains("#")) server->sendMessageToAllClients(data, clientSocket, name);
            if(data=="#help\r\n")
            {
                clientSocket->write("#exit | Disconnect\r\n#allchat | activate/deactivate allchat\r\n#name | set name\r\n");
            }
            if(data.contains("#name"))
            {
                qDebug() << "trying to write name";
                name = data.trimmed();
                name.replace("#name ","");
            }
        }

}

void Client::closedClientConnection()
{
        server->removeClient(this);
        socket->deleteLater();
}

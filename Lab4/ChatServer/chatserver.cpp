#include "chatserver.h"
#include "serverworker.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>  // 添加这个头文件


ChatServer::ChatServer(QObject *parent):
    QTcpServer(parent)
{

}

// 添加检查用户名是否重复的方法
bool ChatServer::isUsernameTaken(const QString &username)
{
    for(ServerWorker *worker : m_clients){
        if(worker->userName() == username){
            return true;  // 用户名已存在
        }
    }
    return false;  // 用户名可用
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker =new ServerWorker(this);
    if(!worker->setSocketDescriptor(socketDescriptor)){
        worker->deleteLater();
        return;
    }
    connect(worker,&ServerWorker::logMessage,this,&ChatServer::logMessage);
    connect(worker,&ServerWorker::jsonReceived,this,&ChatServer::jsonReceived);
    connect(worker,&ServerWorker::disconnectedFromClient,this,std::bind(&ChatServer::userDisconnected,this,worker));

    m_clients.append(worker);
    emit logMessage("新的用户连接上了");
}

void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for(ServerWorker *worker:m_clients){
        worker->sendJson(message);
    }
}

void ChatServer::stopServer()
{
    close();
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &docObj)
{
    const QJsonValue typeVal = docObj.value("type");
    if(typeVal.isNull() || !typeVal.isString())
        return;
    if(typeVal.toString().compare("message",Qt::CaseInsensitive) == 0){
        const QJsonValue textVal = docObj.value("text");
        if(textVal.isNull() || !textVal.isString())
            return;
        const QString text = textVal.toString().trimmed();
        if(text.isEmpty())
            return;
        QJsonObject message;
        message["type"] = "message";
        message["text"] = text;
        message["sender"] = sender->userName();

        broadcast(message,sender);
    }else if(typeVal.toString().compare("login",Qt::CaseInsensitive) == 0){
        const QJsonValue usernameVal = docObj.value("text");
        if(usernameVal.isNull() || !usernameVal.isString())
            return;

        const QString username = usernameVal.toString().trimmed();
        if(username.isEmpty()) {
            // 用户名为空，发送错误信息
            QJsonObject errorMessage;
            errorMessage["type"] = "loginError";
            errorMessage["text"] = "用户名不能为空";
            sender->sendJson(errorMessage);
            return;
        }

        // 检查用户名是否已存在
        if(isUsernameTaken(username)) {
            // 用户名重复，发送错误信息
            QJsonObject errorMessage;
            errorMessage["type"] = "loginError";
            errorMessage["text"] = "用户名已存在，请选择其他用户名";
            sender->sendJson(errorMessage);

            // 在服务器控制台输出错误信息
            qDebug() << "登录失败：用户名" << username << "已存在";
            emit logMessage(QString("登录失败：用户名%1已存在").arg(username));
            return;
        }

        sender->setUserName(username);
        QJsonObject connectedMessage;
        connectedMessage["type"] = "newuser";
        connectedMessage["username"] = username;
        broadcast(connectedMessage,sender);

        QJsonObject userListMessage;
        userListMessage["type"] = "userlist";
        QJsonArray userlist;
        for(ServerWorker *worker : m_clients){
            if(worker == sender)
                userlist.append(worker->userName() + "*");
            else
                userlist.append(worker->userName());
        }
        userListMessage["userlist"] = userlist;
        sender->sendJson(userListMessage);

        // 在服务器控制台输出成功信息
        qDebug() << "用户" << username << "登录成功";
        emit logMessage(QString("用户%1登录成功").arg(username));
    }
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);
    const QString userName = sender->userName();
    if(!userName.isEmpty()){
        QJsonObject disconnectedMessage;
        disconnectedMessage["type"] = "userdisconnected";
        disconnectedMessage["username"] = userName;
        broadcast(disconnectedMessage,nullptr);
        emit logMessage(userName + " disconnected");
    }
    sender->deleteLater();
}

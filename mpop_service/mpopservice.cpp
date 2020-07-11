#include "mpopservice.h"

#include <QtWebSockets>
#include <exception>
#include <QtCore>
#include <QDebug>
#include <cstdio>
#include "notification.h"
#include <iostream>

QT_USE_NAMESPACE

/**
 * @brief Returns an identifier for a given Websocket client.
 * @param peer Websocket client.
 * @return Host and port, concatenated.
 */
static QString getIdentifier(QWebSocket* peer) {
    return QStringLiteral("%1:%2").arg(peer->peerAddress().toString(),
        QString::number(peer->peerPort()));
}

MPopService::MPopService(const Config& config, QObject* parent) :
        QObject(parent),
        m_pWebSocketServer(new QWebSocketServer(QStringLiteral("MPOP Service"), QWebSocketServer::NonSecureMode, this)),
        _facade(config),
        _config(config)
{
    quint16 port = config.service_port_number;
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        QTextStream(stdout) << "Server listening on port " << port << '\n';
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,  this, &MPopService::newConnectionCb);
    }
}

MPopService::~MPopService() {
    m_pWebSocketServer->close();
}

void MPopService::newConnectionCb() {
    auto socket = m_pWebSocketServer->nextPendingConnection();
    QTextStream(stdout) << getIdentifier(socket) << " connected!\n";
    socket->setParent(this);
    connect(socket, &QWebSocket::textMessageReceived, this, &MPopService::textMessageReceivedCb);
    connect(socket, &QWebSocket::disconnected,  this, &MPopService::socketDisconnectedCb);
    m_clients << socket;
}

void MPopService::textMessageReceivedCb(const QString &message) {
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    bool broadcastNotification = false;

    QTextStream(stdout) << "got a request";
    try {
        QString response = this->handleJsonRpcTwoMethod(message, broadcastNotification);

        if (broadcastNotification) {
            QString notification = response;
            for (QWebSocket *pClient : qAsConst(m_clients)) {
                if (pClient != pSender) { //don't echo message back to sender
                    pClient->sendTextMessage(notification);
                }
            }
        } else {
            pSender->sendTextMessage(response);
        }
    } catch (const std::exception& e) {
        //qDebug << e.what();
    }
}


void MPopService::socketDisconnectedCb() {
    QWebSocket *client = qobject_cast<QWebSocket*>(sender());
    QTextStream(stdout) << getIdentifier(client) << " disconnected!\n";
    if (client) {
        m_clients.removeAll(client);
        client->deleteLater();
    }
}


QString MPopService::handleJsonRpcTwoMethod(const QString& message, bool &broadcastNotification) {
    //std::string str = message.toStdString();
    //QJsonDocument requestDocument = QJsonDocument::fromRawData(str.c_str(), str.size(), QJsonDocument::Validate);
    Request request = Request::fromString(message);
    //if (document == nullptr) {
    //    qDebug << "Could not parse JSON from JSON-RPC 2.0 message.";
    //}
    Response response;
    response.id = request.id; // FIXME: should allow string, int or null
    response.method = request.method;
    bool sendResponse = true;

    if (request.method == "message") {
        QTextStream(stdout) << "Got method message" << endl;
        //response.result = QVariant::fromValue(QString("pong"));
        QTextStream(stdout) << "Answer with pong" << endl;
        sendResponse = false;
        broadcastNotification = true;
        Notification notification;
        notification.method = "message";
        notification.paramsByPosition = request.paramsByPosition;
        QString ret = notification.toString();
        QTextStream(stdout) << "Response: " << ret;
        return ret;
    } else if (request.method == "ping") {
        QTextStream(stdout) << "Got method ping" << endl;
        response.result = QVariant::fromValue(QString("pong"));
        QTextStream(stdout) << "Answer with pong" << endl;
    } else if (request.method == "echo") {
        QTextStream(stdout) << "Got method echo" << endl;
        response.result = QVariant(request.paramsByName);
        QTextStream(stdout) << "Answer with echo" << endl;
    } else if (this->handleFacadeMethod(request, response)) {
        // success
    } else {
        QTextStream(stdout) << "unhandled request";
    }

    QString ret = response.toString(); // return string response (JSON)
    QTextStream(stdout) << "Response: " << ret;
    return ret;
}

bool MPopService::handleFacadeMethod(const Request& request, Response& response) {
    // Write to the response object.
    QString method = request.method;
    if (method == "getOrCreateUser") {
        QString rfidTag = request.paramsByPosition[0].toString();
        response.result = QVariant(this->_facade.getOrCreateUser(rfidTag));
// TODO int (const QString& rfidTag);
    }

    // TODO QString getUserLanguage(int userId);

    // TODO QMap<QString, int> getUserAnswers(int userId);
    // TODO void setUserAnswer(int userId, const QString& questionId, int value);
    // TODO QList<int> getStatsForQuestion(const QString& questionId);
    // TODO void freeTag(const QString& rfidTag);
    // TODO void freeUnusedTags();
    // TODO bool setUserLanguage(int userId, const QString& language);
    // TODO bool setUserGender(int userId, const QString& gender);
    // TODO QString getUserGender(int userId);

    return true;
}

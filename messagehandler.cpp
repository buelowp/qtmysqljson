/*
 * Copyright (c) 2019 <copyright holder> <email>
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "messagehandler.h"

MessageHandler::MessageHandler(QObject *parent) : QObject(parent)
{
    setupMqttSubscriber();
}

MessageHandler::~MessageHandler()
{
}

void MessageHandler::connectionComplete()
{
    qDebug() << __PRETTY_FUNCTION__ << ": Connected to MQTT server";
    m_mqttClient->subscribe("database/request/#");
}

void MessageHandler::disconnectedEvent()
{
    qDebug() << __PRETTY_FUNCTION__ << ": Disconnected from MQTT server";
    m_mqttClient->connectToHost();
}

void MessageHandler::queryTable(QString database, QString table)
{
    DBInterface db;
    QJsonDocument doc;
    QMQTT::Message message;
    
    if (db.open(database)) {
        if (db.getTableContents(table, &doc)) {
            message.setTopic("database/response/querytableresponse");
            message.setPayload(doc.toJson(QJsonDocument::Compact));
            m_mqttClient->publish(message);
        }
    }
}

void MessageHandler::queryTable(QString database, QString table, QString query)
{
    DBInterface db;
    QJsonDocument doc;
    QMQTT::Message message;
    
    if (db.open(database)) {
        if (db.getTableContents(table, query, &doc)) {
            message.setTopic("database/response/querytablewithqueryresponse");
            message.setPayload(doc.toJson(QJsonDocument::Compact));
            m_mqttClient->publish(message);
        }
    }    
}

void MessageHandler::messageReceivedOnTopic(QString topic, QString message)
{
    qDebug() << __PRETTY_FUNCTION__ << ": Message received for topic" << topic;
    if (topic == "database/request/querytable") {
        QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8().data());
        if (!doc.isEmpty() || !doc.isNull()) {
            qDebug() << __PRETTY_FUNCTION__ << ": JSON is valid";
            QJsonObject obj = doc.object();
            if (obj.contains("database") && obj.contains("table"))
                queryTable(obj["database"].toString(), obj["table"].toString());
        }
        else {
            qDebug() << __PRETTY_FUNCTION__ << message;
        }
    }
    if (topic == "database/request/querytablewithquery") {
        QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8().data());
        if (!doc.isEmpty() || !doc.isNull()) {
            QJsonObject obj = doc.object();
            if (obj.contains("database") && obj.contains("table") && obj.contains("query"))
                queryTable(obj["database"].toString(), obj["table"].toString(), obj["query"].toString());
        }
    }
}

void MessageHandler::setupMqttSubscriber()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "qtmyssqljson", "qtmyssqljson");
    QString hostname = settings.value("mqttserver").toString();
    QHostInfo lookup = QHostInfo::fromName(hostname);
    QList<QHostAddress> addresses = lookup.addresses();
    
    if (addresses.size() > 0) {
        m_mqttClient = new QMqttSubscriber(addresses.at(0), settings.value("mqttport").toInt(), this);
        qDebug() << __PRETTY_FUNCTION__ << ": setting host address to" << addresses.at(0);
    }
    else {
        m_mqttClient = new QMqttSubscriber(QHostAddress::LocalHost, settings.value("mqttport").toInt(), this);
        qDebug() << __PRETTY_FUNCTION__ << ": Using localhost";
    }
    
    if (m_mqttClient) {
        connect(m_mqttClient, SIGNAL(connectionComplete()), this, SLOT(connectionComplete()));
        connect(m_mqttClient, SIGNAL(disconnectedEvent()), this, SLOT(disconnectedEvent()));
        connect(m_mqttClient, SIGNAL(messageReceivedOnTopic(QString, QString)), this, SLOT(messageReceivedOnTopic(QString, QString)));
        m_mqttClient->connectToHost();
    }
}

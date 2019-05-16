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

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QtCore/QtCore>
#include "dbinterface.h"
#include "qmqttsubscriber.h"

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    MessageHandler(QObject *parent = 0);
    ~MessageHandler();
    
    void setupMqttSubscriber();

public Q_SLOTS:
    void connectionComplete();
    void disconnectedEvent();
    void messageReceivedOnTopic(QString, QString);
    
private:
    void queryTable(QString, QString);
    void queryTable(QString, QString, QString);

    QMqttSubscriber *m_mqttClient;
};

#endif // MESSAGEHANDLER_H

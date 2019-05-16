#include "dbinterface.h"

DBInterface::DBInterface(QObject *parent) : QObject(parent)
{
}

DBInterface::~DBInterface()
{
    m_database.close();
}

bool DBInterface::open(QString db)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "dbinterface", "dbinterface");
    
    m_database = QSqlDatabase::addDatabase("QMYSQL");
    m_database.setHostName(settings.value("hostname").toString());
    m_database.setUserName(settings.value("username").toString());
    m_database.setPassword(settings.value("password").toString());
    m_database.setDatabaseName(db);
    
    return m_database.open();
}

void DBInterface::close()
{
    m_database.close();
}

bool DBInterface::getTableContents(QString table, QByteArray *results)
{
    Q_UNUSED(results)
    
    if (!m_database.isOpen()) {
        qDebug() << __PRETTY_FUNCTION__ << ": Database is not open";
        return false;
    }
    
    QSqlQueryModel model;
    QString query = QString("SELECT * FROM %1").arg(table);
    model.setQuery(query);
    QJsonDocument doc;
    QJsonObject header;
    QJsonObject sql;
    QJsonArray rows;

    qDebug() << __PRETTY_FUNCTION__ << ": Getting data from" << table;
    sql["table"] = table;
    for (int i = 0; i < model.rowCount(); ++i) {
        QJsonObject row;
        for (int j = 0; j < model.record(i).count(); j++) {
            row[model.record(i).fieldName(j)] = model.record(i).value(j).toString();
        }
        rows.append(QJsonValue(row));
    }
    sql["rows"] = rows;
    doc.setObject(sql);
    qDebug() << doc.toJson();
    return false;
}

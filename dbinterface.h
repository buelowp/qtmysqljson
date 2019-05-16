#ifndef dbinterface_H
#define dbinterface_H

#include <QtCore/QtCore>
#include <QtSql/QtSql>

class DBInterface : public QObject
{
    Q_OBJECT

public:
    DBInterface(QObject *parent = 0);
    virtual ~DBInterface();
    
    bool open(QString);
    void close();
    bool getTableContents(QString, QByteArray*);

private:
    QSqlDatabase m_database;
    bool m_databaseSelected;
};

#endif // dbinterface_H

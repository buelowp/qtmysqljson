#ifndef dbinterface_H
#define dbinterface_H

#include <QObject>

class dbinterface : public QObject
{
    Q_OBJECT

public:
    dbinterface();
    virtual ~dbinterface();

private slots:
    void output();
};

#endif // dbinterface_H

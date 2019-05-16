#include <QCoreApplication>
#include "dbinterface.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    DBInterface dbi;
    
    if (dbi.open("fishfacts")) {
        dbi.getTableContents("fish", NULL);
    }
    else {
        qDebug() << __PRETTY_FUNCTION__ << ": Unable to open database";
    }
    
    return app.exec();
}

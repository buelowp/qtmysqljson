#include <QCoreApplication>
#include "dbinterface.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    DBInterface dbi;
    QByteArray ba;
    
    return app.exec();
}

#include <QCoreApplication>
#include "dbinterface.h"


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    dbinterface dbinterface;
    return app.exec();
}

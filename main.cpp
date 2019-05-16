#include <QCoreApplication>
#include "dbinterface.h"
#include "messagehandler.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    DBInterface dbi;
    QByteArray ba;
    
    MessageHandler handler;
    
    return app.exec();
}

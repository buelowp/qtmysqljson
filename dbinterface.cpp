#include "dbinterface.h"

#include <QTimer>
#include <iostream>

dbinterface::dbinterface()
{
    QTimer* timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), SLOT(output()) );
    timer->start( 1000 );
}

dbinterface::~dbinterface()
{}

void dbinterface::output()
{
    std::cout << "Hello World!" << std::endl;
}

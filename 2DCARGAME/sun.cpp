#include "sun.h"
#include<QGraphicsScene>


// similar to cloud class check cloud class.
// Contains 2 classes
sun::sun()
{
setPixmap(QPixmap::fromImage(QImage(":/sun.jpg")));
setScale(0.25);
int rx=195+rand()%(266);
setPos(rx,10);
t=new QTimer;
t->start(10);
connect(t,SIGNAL(timeout()),this,SLOT(updatePosition()));
}

void sun::updatePosition()
{
    setY(y()+8);
    if(y()>=700)
    {
        scene()->removeItem(this);
        delete this;
    }
}

boost::boost()
{
    setPixmap(QPixmap::fromImage(QImage(":/boost.png")));
    setScale(0.1);
    int rx=195+rand()%(266);
    setPos(rx,10);
    t=new QTimer;
    t->start(10);
    connect(t,SIGNAL(timeout()),this,SLOT(updatePosition()));
}

void boost::updatePosition()
{
    setY(y()+8);
    if(y()>=700)
    {
        scene()->removeItem(this);
        delete this;
    }
}

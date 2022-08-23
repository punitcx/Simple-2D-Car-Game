#include "cloud.h"
#include<QGraphicsScene>
cloud::cloud()
{
setPixmap(QPixmap::fromImage(QImage(":/cloud.png")));  // set cloud image.
setScale(0.25);                                      // resize
int rx=195+rand()%(266);                             //generate random position.
setPos(rx,10);                                       //display cloud.
t=new QTimer;
t->start(10);
connect(t,SIGNAL(timeout()),this,SLOT(updatePosition())); // Update cloud position every 10 milliseconds.
}

void cloud::updatePosition()
{
    setY(y()+8);               // Move cloud down by 8 pixels.
    if(y()>=700)
    {
        scene()->removeItem(this);    // Delete when it goes out of road.
        delete this;
    }
}

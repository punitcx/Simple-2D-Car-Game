#include "car.h"
#include<QGraphicsScene>

Car::Car()
{

 setFlag(QGraphicsItem::ItemIsFocusable);   // Set car as focusable,
 setScale(0.5);                             //Resize
 setPos(195+15*0,550);                      //Set position on track
 bomb=new QLabel;                               //Initialise bomb with movie animation
 bomb->setAttribute(Qt::WA_NoSystemBackground);
 movie=new QMovie(":/explosion.gif");
 bomb->setMovie(movie);

}

void Car::keyPressEvent(QKeyEvent *event)    // Keypress slot
{
    if(event->key()==Qt::Key_Left)    //If key is left arrow, move car left
    {
        setX(x()-15);
    }
    else if(event->key()==Qt::Key_Right) // Move car right
    {
        setX(x()+15);
    }
    else if(event->key()==Qt::Key_Up) // Increase speed
    {
        emit(increaseSpeed());
    }
    else if(event->key()==Qt::Key_Down) // Decrease speed
    {
        emit(decreaseSpeed());
    }
    if(x()<=180 || x() >=445||coll==1)   // If it is outside road, create bomb animation and hide car/
    {
bomb->show();
movie->start();
        scene()->addWidget(bomb);
        bomb->move(x()-50,y()-80);
        emit(carDistroyed());         // emit car destroyed signal
        hide();      // hide car
        coll=0;

    }
}

void Car::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setX(event->scenePos().x());
    if(event->scenePos().y()-20<y())
        emit(increaseSpeed());
    else if(event->scenePos().y()>y())
        emit(decreaseSpeed());
    QKeyEvent *e=new QKeyEvent(QKeyEvent::KeyPress,Qt::Key_0,Qt::NoModifier);
    keyPressEvent(e);
}

void Car::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        emit(increaseSpeed());
}

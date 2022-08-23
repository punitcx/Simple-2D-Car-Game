#include "spawn.h"
#include<QGraphicsScene>
spawn::spawn()
{
    // similar to car class check car class, work is remaining.
    setPixmap(QPixmap::fromImage(QImage(":/car4.png")));
    setScale(0.5);
    setPos(195+15*5,550);
    bomb=new QLabel;
    movie=new QMovie(":/explosion.gif");
    bomb->setMovie(movie);
    bomb->setAttribute(Qt::WA_NoSystemBackground);
    spawnTimer=new QTimer;
    connect(this,SIGNAL(spawnDistroyed()),this,SLOT(checkSpawnLife()));
    connect(spawnTimer,SIGNAL(timeout()),this,SLOT(scoreIncrement()));
    spawnTimer->start(1000);
}

void spawn::keyPressEvent(QKeyEvent *event)
{

    if(event->key()==Qt::Key_Left)
    {
        setX(x()-25);
    }
    else if(event->key()==Qt::Key_Right)
    {
        setX(x()+25);
    }
    if(x()<=180)
    setX(x()+25);
    if(x()>=445)
        setX(x()-25);
    if(x()<=180 || x() >=445)
    {
movie->start();
        scene()->addWidget(bomb);
        bomb->move(x()-50,y()-80);
        hide();
        bomb->show();
        emit(spawnDistroyed());
    }
}

void spawn::randomMoves()
{
    int num=qrand();
    if(num%30<=10)
        keyPressEvent((new QKeyEvent(QKeyEvent::KeyPress,Qt::Key_Left,Qt::NoModifier)));
    else if(num%30>=11&&num%30<=20)
        keyPressEvent((new QKeyEvent(QKeyEvent::KeyPress,Qt::Key_Right,Qt::NoModifier)));
    else
        keyPressEvent((new QKeyEvent(QKeyEvent::KeyPress,Qt::Key_Up,Qt::NoModifier)));
}

void spawn::checkSpawnLife()
{
    life--;
    if(life==0)
        hide();
    else
    {
        setPos(195+15*4,550);
        spawnTimer->start(2000);       //else restart game after 2 seconds.
       connect(spawnTimer,SIGNAL(timeout()),this,SLOT(stopAnimation()));
    }
}

void spawn::stopAnimation()
{
    bomb->hide();
    show();
    disconnect(spawnTimer,SIGNAL(timeout()),this,SLOT(stopAnimation()));
    spawnTimer->start(1000);
}

void spawn::scoreIncrement()
{
    score+=qrand()%4;
}

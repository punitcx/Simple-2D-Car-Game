#include "track.h"
track::track()
{
    TrackImage=new QPixmap(":/Longtrack.PNG"); // set track image and  scale it
    *TrackImage=TrackImage->scaled(TrackImage->size()*1.8);
    setPixmap(*TrackImage);
    setPos(0,-700);
t=new QTimer;
connect(t,SIGNAL(timeout()),this,SLOT(updateTrack())); // update every 10 milliseconds.
update=new QTimer;
update->start(100);
m=new QMediaPlayer;
m->setMedia(QMediaContent(QUrl("qrc:/carrrunning.mp3")));
m->setVolume(100);
}

void track::updateTrack()
{
    if(m->state()==QMediaPlayer::StoppedState&&speed!=0)
    m->play();
    else if(speed==0)
        m->stop();
    setPos(0,y()+speed);   // mov track down by 8 pixels every 10 milliseconds
    //qDebug()<<y();
    if(y()>=20)
        setPos(0,-700);   // repeat the same track again and again.
}

void track::stopMovingTrack()  //stop timer
{
    t->stop();
}

void track::startMovingTrack()  //start timer
{
 t->start(10);
}

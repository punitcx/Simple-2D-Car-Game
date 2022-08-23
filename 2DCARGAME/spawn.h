#ifndef SPAWN_H
#define SPAWN_H
#include<QGraphicsPixmapItem>
#include<QKeyEvent>
#include<QLabel>
#include<QMovie>
#include<QTimer>
class spawn : public  QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
signals:
    void spawnDistroyed();
public:
    spawn();
    QLabel *bomb;
    QMovie *movie;
    float dis_trav=0;
    int life=3,score=0;
    int id=4,status=0;
    QTimer *spawnTimer;
    void keyPressEvent(QKeyEvent *event);
    void randomMoves();
public slots:
    void checkSpawnLife();
    void stopAnimation();
    void scoreIncrement();

};

#endif // SPAWN_H

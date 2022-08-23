#ifndef CAR_H
#define CAR_H
#include<QGraphicsPixmapItem>
#include<QKeyEvent>
#include<QLabel>
#include<QMovie>
#include<QGraphicsSceneMouseEvent>
class Car : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
signals:
    void carDistroyed();
    void increaseSpeed();
    void decreaseSpeed();
public:
    Car();
    QLabel *bomb;    // Bomb Label
    QMovie *movie;   // Bomb animation
    float dis_trav=0;
    int coll=0;
    void keyPressEvent(QKeyEvent *event);  //keypress or moving car.
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CAR_H

#ifndef SUN_H
#define SUN_H
#include<QGraphicsPixmapItem>
#include<QTimer>

//Class for sun
class sun : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    sun();
    QTimer *t;
public slots:
    void updatePosition();
};


// Class for creating Boost for battery
class boost: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    boost();
    QTimer *t;
public slots:
    void updatePosition();
};

#endif // SUN_H

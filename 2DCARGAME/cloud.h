#ifndef CLOUD_H
#define CLOUD_H

#include<QGraphicsPixmapItem>
#include<QTimer>
class cloud : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    cloud();
QTimer *t;
public slots:
    void updatePosition();  // Update cloud position
};

#endif // CLOUD_H

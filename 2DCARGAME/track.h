#ifndef TRACK_H
#define TRACK_H
#include<QGraphicsPixmapItem>
#include<QKeyEvent>
#include<QGraphicsScene>
#include<QTimer>
#include<QtMultimedia/QMediaPlayer>
class track :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    track();
    QPixmap *TrackImage;
    QTimer *t,*update;
    int speed=8;
    QMediaPlayer *m;
public slots:          // Track slot functions
    void updateTrack();
    void stopMovingTrack();
    void startMovingTrack();
};

#endif // TRACK_H

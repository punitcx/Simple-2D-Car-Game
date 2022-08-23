#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QGraphicsView>
#include<QPixmap>
#include<QUdpSocket>
#include<QByteArray>
#include<QLabel>
#include<car.h>
#include<track.h>
#include<battery.h>
#include<sun.h>
#include<cloud.h>
#include<spawn.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGraphicsScene *Scene;
    battery *Battery;
    Car *RaceCar;
    track *RaceTrack;
    QGraphicsTextItem *Score,*Life;
    int currentscore=0;
    QTimer *addobstacles,*collisionTimer,*spawnTimer;
    int level=1,life=3;
    spawn *Spawn1,*Spawn2,*Spawn3;
    QMediaPlayer *media;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    int ishost=0,status=1;
    int id=1;

public slots:
    void startDialog();
    void checkCollison();
    void stopGame();
    void startGame();
    void showScores();
    void setCarLogo();
    void createSpawn();
    void addSpawnstoScene();
    void createRaceCar();
    void updateDistance();
    void increaseSpeed();
    void decreaseSpeed();
    void receiveDetails();
    void sendDetails();


private slots:
    void on_startRacing_clicked();
    void addCloud();
    void addSun();
    void addBoost();
    void addSomething();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

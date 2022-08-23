#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFileDialog>
#include<typeinfo>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
showMaximized();   // Show maximised window.

startDialog();  // Set initial start page

 media=new QMediaPlayer;


ui->Background->setPixmap(QPixmap(":/frontBack.jpg"));  // set background image.
ui->Background->setScaledContents(true); // Fit the background.


    Scene=new QGraphicsScene(ui->graphicsView->rect()); //Create a graphics scene
    ui->graphicsView->setScene(Scene);     // Set scene

    RaceTrack=new track();      // Create racetrackk with default size and track image.
    Scene->addItem(RaceTrack);  // Add to scene.
    int w=RaceTrack->TrackImage->width();
    Scene->setSceneRect(0,0,w,680);         // Set fixed height,width

    ui->graphicsView->setFixedWidth(w);   // Set fixed height,width for graphics view also.
    ui->graphicsView->setFixedHeight(680);

    Score=new QGraphicsTextItem("Score : \n0");   // create score object with font and position
    Score->setFont(QFont("",15));
    Score->setPos(20,10);
    Scene->addItem(Score);                             // and add to scene
    Life=new QGraphicsTextItem("Life : \n3");        // create life object with font and position
    Life->setFont(QFont("",20));
    Life->setPos(20,280);
    Scene->addItem(Life);                      // and add to scene

    QGraphicsTextItem *BatteryLabel=new QGraphicsTextItem("Battery : \n");     // create batterylabel object with font and position
    BatteryLabel->setFont(QFont(" ",20));
    BatteryLabel->setPos(w-160,10);           //left side
    Scene->addItem(BatteryLabel);               // add


    Battery=new battery();   // create Battery Progressbar object .
    Scene->addWidget(Battery);
    Battery->move(w-160,50);  // Set Position 


    addobstacles=new QTimer;
    collisionTimer=new QTimer;  // Create timer to check collisions

    sender=new QUdpSocket(this);

    receiver=new QUdpSocket(this);
    receiver->bind(45454, QUdpSocket::ShareAddress);
    //receiver->joinMulticastGroup(QHostAddress::LocalHost);
    setFixedSize(698+50,680);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startDialog()
{
    ui->stackedWidget->setCurrentIndex(0); // First page of stacked widget
}

void MainWindow::checkCollison()  // check colliding items withh car
{
    QList<QGraphicsItem*> Colliding=RaceCar->collidingItems();
    foreach (QGraphicsItem* item, Colliding) {
        if(typeid(*item)==typeid(sun))    // if it is sun, 10 points
        {
            media->setVolume(60);
            Battery->setValue(Battery->value()+10);
            currentscore+=10;
            Scene->removeItem(item);
            delete item;                    // delete immediately
        }
        else if(typeid(*item)==typeid(cloud)){  // if it is cloud, -20 points
            media->setMedia(QUrl("qrc:/cloudrain.mp3"));
            media->play();
            Battery->setValue(Battery->value()-10);
            currentscore-=10;
            currentscore=currentscore<0?0:currentscore;
            if(currentscore==0)
                stopGame();
            Scene->removeItem(item);
            delete item;
        }
        else if(typeid(*item)==typeid(boost)){ //if it is boost, fill battery.

            media->setMedia(QUrl("qrc:/flash.mp3"));
            media->setVolume(60);
            media->play();
            Battery->setValue(100);
            Scene->removeItem(item);
            delete item;
        }
        else if(typeid(*item)==typeid(spawn)){  // if it is cloud, -20 points

            Battery->setValue(Battery->value()-20);
            currentscore-=10;
            currentscore=currentscore<0?0:currentscore;
                RaceCar->coll=1;
        }
    }   

}
void MainWindow::stopGame()
{
    media->setMedia(QUrl("qrc:/carby.mp3"));
    media->play();
    life--;    // if car is destroyed, decrement life.
    Life->setHtml(QString("Life : \n%1").arg(life));  // Update life label
    RaceTrack->speed=0;    //stop all the things
    addobstacles->stop();
    collisionTimer->stop();
    disconnect(addobstacles,SIGNAL(timeout()),this,SLOT(addSomething()));
    disconnect(collisionTimer,SIGNAL(timeout()),this,SLOT(checkCollison()));
    if(life==0)
    showScores();  // if life is 0, show scores
    else
    {
        addobstacles->start(2000);       //else restart game after 2 seconds.
       connect(addobstacles,SIGNAL(timeout()),this,SLOT(startGame()));
    }
}

void MainWindow::startGame()
{

    disconnect(addobstacles,SIGNAL(timeout()),this,SLOT(startGame()));
    RaceCar->bomb->movie()->stop();  // stop the animation and hide it.
    RaceCar->bomb->hide();
    RaceCar->setPos(195+15*0,550);   // reset car position
    RaceCar->show();            // show car
    RaceCar->setFocus();
    RaceTrack->startMovingTrack();   // start all the things....
    level=ui->horizontalSlider->value()+1;
    addobstacles->start(1000);
    collisionTimer->start(100);
    connect(addobstacles,SIGNAL(timeout()),this,SLOT(addSomething()));
    connect(collisionTimer,SIGNAL(timeout()),this,SLOT(checkCollison()));
}

void MainWindow::showScores()
{
    media->stop();
    media->setMedia(QUrl("qrc:/full.mp3"));
    media->setPosition(25*1000);
    media->setVolume(100);
    media->play();
    ui->Player1name->setText(ui->Myname->text());  //show name and score
    ui->Player1score->setText(QString::number(currentscore));
    ui->Player2score->setText(QString::number(Spawn1->score));
    ui->Player3score->setText(QString::number(Spawn2->score));
    ui->Player4score->setText(QString::number(Spawn3->score));
ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::setCarLogo()
{
    QPixmap *carLogo;  // set car logo according to user.
    QMatrix rm;        // rotations are used because some cars are rotated already.
                       // please find good car logos online.
    if(ui->Car_1->isChecked())
    {
        id=1;
        carLogo=new QPixmap(":/car1.png");
                rm.rotate(-90);
                *carLogo = carLogo->transformed(rm);
    }
    else if(ui->Car_2->isChecked())
    {
        id=2;
        carLogo=new QPixmap(":/car2.png");
                rm.rotate(180);
                *carLogo = carLogo->transformed(rm);
    }
    else if(ui->Car_3->isChecked())
    {
        id=3;
        carLogo=new QPixmap(":/car3.png");
        RaceCar->setScale(0.4);
                rm.rotate(90);
                *carLogo = carLogo->transformed(rm);
    }
    else if(ui->Car_4->isChecked())
    {
        id=4;
        carLogo=new QPixmap(":/car4.png");
                *carLogo = carLogo->transformed(rm);
    }
    RaceCar->setPixmap(*carLogo);   // set logo according to above conditions.
}

void MainWindow::createSpawn()
{
    Spawn1=new spawn();
    Spawn1->id=2;
    Spawn1->setPixmap(QPixmap::fromImage(QImage(":/car4.png")));

    Spawn2=new spawn();
    Spawn2->id=3;
    Spawn2->setPixmap(QPixmap::fromImage(QImage(":/car4.png")));
    Spawn2->setPos(195+15*7,550);

    Spawn3=new spawn();
    Spawn3->id=4;
    Spawn3->setPixmap(QPixmap::fromImage(QImage(":/car4.png")));
    Spawn3->setPos(195+15*10,550);
    //connect(Spawn1,SIGNAL(spawnDistroyed()),this,SLOT(checkSpawnLife()));
}

void MainWindow::addSpawnstoScene()
{
    Scene->addItem(Spawn1);
    Scene->addItem(Spawn2);
    Scene->addItem(Spawn3);
}

void MainWindow::createRaceCar()
{
    RaceCar=new Car();
    Scene->addItem(RaceCar);
    connect(RaceCar,SIGNAL(carDistroyed()),this,SLOT(stopGame()));
}

void MainWindow::updateDistance()
{
    if(RaceCar->isVisible())
     RaceCar->dis_trav+=0.001*(RaceTrack->speed/8.0);  // set distance according to speed.
    if(Spawn1->isVisible()&&Spawn1->status!=1)
    {Spawn1->dis_trav+=0.004;         //max is 0.005
    Spawn1->randomMoves();}
    if(Spawn2->isVisible()&&Spawn2->status!=1)
    {Spawn2->dis_trav+=0.0037;
    Spawn2->randomMoves();}
    if(Spawn3->isVisible()&&Spawn3->status!=1)
    {Spawn3->dis_trav+=0.0035+(qrand()%2)/1000;
    Spawn3->randomMoves();}


    int diff=(Spawn1->dis_trav-RaceCar->dis_trav)*1000*8;
    Spawn1->setY(550-diff);
    diff=(Spawn2->dis_trav-RaceCar->dis_trav)*1000*8;
    Spawn2->setY(550-diff);
    diff=(Spawn3->dis_trav-RaceCar->dis_trav)*1000*8;
    Spawn3->setY(550-diff);
}

void MainWindow::increaseSpeed()
{
    if(RaceTrack->speed!=40)
    RaceTrack->speed++;    //decrease timer frequency
}

void MainWindow::decreaseSpeed()
{
    if(RaceTrack->speed!=0)
        RaceTrack->speed--;        // increase timer frequency
}

void MainWindow::sendDetails()
{
//    QString p2details=QString("%1 %2 %3 %4").arg(Spawn1->id).arg(Spawn1->x()).arg(Spawn1->dis_trav).arg(Spawn1->score);
//    QString p3details=QString("%1 %2 %3 %4").arg(Spawn2->id).arg(Spawn2->x()).arg(Spawn2->dis_trav).arg(Spawn2->score);
//    QString p4details=QString("%1 %2 %3 %4").arg(Spawn3->id).arg(Spawn3->x()).arg(Spawn3->dis_trav).arg(Spawn3->score);
//    if(ishost){
//    datagram = QString("%1 %2 %3 %4").arg(p1details).arg(p2details).arg(p3details).arg(p4details).toUtf8();
//    sender->writeDatagram(datagram.data(), datagram.size(),QHostAddress::Broadcast, 45454);
//              }
    QByteArray datagram;
    QString p1details=QString("%1 %2 %3 %4").arg(id).arg(RaceCar->x()).arg(RaceCar->dis_trav).arg(currentscore);

        datagram = p1details.toUtf8();
        sender->writeDatagram(datagram.data(), datagram.size(),QHostAddress::Broadcast, 45454);
}

void MainWindow::receiveDetails()
{
    QList<QString> details;
    while (receiver->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(), datagram.size());
        if(QString(datagram)=="st"&&ui->startRacing->isVisible())
        {
            on_startRacing_clicked();
        }
        details=QString(datagram).simplified().split(' ');
        int receivedid=details.at(0).toInt();
        if(Spawn1->id==receivedid){
        Spawn1->status=1;
Spawn1->setPixmap(QPixmap::fromImage(QImage(":/car"+details.at(0)+".png")));
    Spawn1->setX(details.at(1).toInt());
    Spawn1->dis_trav=details.at(2).toFloat();
    Spawn1->score=details.at(3).toInt();}
else if(Spawn2->id==receivedid){
            Spawn2->status=1;
    Spawn2->setPixmap(QPixmap::fromImage(QImage(":/car"+details.at(0)+".png")));
    Spawn2->setX(details.at(1).toInt());
    Spawn2->dis_trav=details.at(2).toFloat();
    Spawn2->score=details.at(3).toInt();}
else if(Spawn3->id==receivedid){
            Spawn3->status=1;
    Spawn3->setPixmap(QPixmap::fromImage(QImage(":/car"+details.at(0)+".png")));
    Spawn3->setX(details.at(1).toInt());
    Spawn3->dis_trav=details.at(2).toFloat();
    Spawn3->score=details.at(3).toInt();}

    }
}

void MainWindow::on_startRacing_clicked()  // start racing button
{
    ui->startRacing->setVisible(false);
    createRaceCar();
    setCarLogo();
    ui->stackedWidget->setCurrentIndex(1);  //2nd page of racing.
    createSpawn();
    addSpawnstoScene();
    startGame();     //start the game
    connect(RaceTrack->update,SIGNAL(timeout()),this,SLOT(updateDistance())); // update every 10 milliseconds.
    connect(RaceCar,SIGNAL(increaseSpeed()),this,SLOT(increaseSpeed())); // update every 10 milliseconds.
    connect(RaceCar,SIGNAL(decreaseSpeed()),this,SLOT(decreaseSpeed())); // update every 10 milliseconds.
    QByteArray datagram;
    QString p1details="st";
        datagram = p1details.toUtf8();
        sender->writeDatagram(datagram.data(), datagram.size(),QHostAddress::Broadcast, 45454);
}

void MainWindow::addCloud()
{

    cloud *Cloud=new cloud();   // add cloud object
    Scene->addItem(Cloud);
}

void MainWindow::addSun()   // add sun object
{
    sun *Sun=new sun();
    Scene->addItem(Sun);

}

void MainWindow::addBoost()  // add super charge boost object
{
    boost *Boost=new boost();
    Scene->addItem(Boost);
}

void MainWindow::addSomething()  // update battery and score
{
    Battery->setValue(Battery->value()-1);
    if(Battery->value()<=0)
        stopGame();
    Score->setHtml(QString("Score : <br>%1<br> Spawn 1 Score :<br>%2<br>Spawn 2 Score :<br>%3<br>Spawn 3 Score :<br>%4<br>").arg(currentscore++).arg(Spawn1->score).arg(Spawn2->score).arg(Spawn3->score));
    if(Battery->value()<=20)
        Battery->setStyleSheet("QProgressBar::chunk {background:red;}"); // if low battery then red color.
    else
        Battery->setStyleSheet("QProgressBar::chunk {background:green;}"); // else green color.

    //Randomly add things according to the level selected.


    int num=qrand();
    // just a random function, don't think much. You can modify it if you want.
    if(addobstacles->remainingTime()%2==1){
    if(num%30<=5*(4-level))
        addSun();
    else if(num%30>=6*(4-level)&&num%30<=22+level)
        addCloud();
    else
        addBoost();
                                }

    if(qrand()%25==0)
    {
        media->setMedia(QUrl("qrc:/full.mp3"));
        media->setVolume(100);
        media->play();
    }

}

void MainWindow::on_pushButton_clicked()
{
    connect(collisionTimer,SIGNAL(timeout()),this,SLOT(sendDetails()));
    connect(receiver,SIGNAL(readyRead()),this,SLOT(receiveDetails()));
}


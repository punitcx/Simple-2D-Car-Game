#ifndef BATTERY_H
#define BATTERY_H

#include<QProgressBar>

class battery : public QProgressBar
{
    Q_OBJECT
public:
    battery();
public slots:
    void setProgress(); //set Battery Progress
};

#endif // BATTERY_H

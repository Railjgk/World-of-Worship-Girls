#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "w_battle.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(w_battle *w = nullptr):my_w(w){};
    void run() override;
private:
    w_battle* my_w;
signals:

};

#endif // MYTHREAD_H

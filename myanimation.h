#ifndef MYANIMATION_H
#define MYANIMATION_H

#include <QObject>
#include <QGraphicsColorizeEffect>
#include"worship.h"

class MyAnimation : public QObject
{
    Q_OBJECT
public:
    explicit MyAnimation(QObject *parent = nullptr);
    void performAttack(worship*& attacker, worship*& theAttacked);
    void performAttackP(worship*& attacker, worship*& theAttacked);
    //void performExtratk(worship* order1);
    void performDead(worship*& w);
    void performDeadP(worship*& w);
signals:
    void signalFinishAttack();
};

#endif // MYANIMATION_H

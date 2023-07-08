#include "myanimation.h"

MyAnimation::MyAnimation(QObject *parent)
    : QObject{parent}
{

}

void MyAnimation::performAttack(worship*&attacker, worship *&theAttacked)
{
    // 播放攻击动画和受击效果
    attacker->label->setMovie(attacker->AttackMovie);
    QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(theAttacked->label);
    QGraphicsColorizeEffect* effect1 = new QGraphicsColorizeEffect(attacker->label);

    // 连接frameChanged信号与槽函数
    QEventLoop loop;
    connect(attacker->AttackMovie, &QMovie::frameChanged, attacker->label, [&](int frameNumber){
        // 如果动画播放到最后一帧，停止动画
        //qDebug() << "hhhhh" << Qt::endl;
        //qDebug() << attacker->AttackMovie->frameCount() << Qt::endl;
        if (frameNumber == attacker->AttackMovie->frameCount() - 1) {
            attacker->AttackMovie->stop(); // 停止动画
            // 动画播放完成后发送信号：调回stand动画
            attacker->performStand();
            //emit signalFinishAttack();
            effect->setEnabled(false); // 禁用效果
            effect1->setEnabled(false);
            loop.quit();
        }
    });
    attacker->AttackMovie->start();
    effect1->setColor(Qt::blue);
    attacker->label->setGraphicsEffect(effect1);
    //theAttacked受击效果
    effect->setColor(Qt::red);
    theAttacked->label->setGraphicsEffect(effect);


    // 等待动画播放完成
    loop.exec();
}

void MyAnimation::performAttackP(worship *&attacker, worship *&theAttacked)
{
    // 播放攻击动画和受击效果
    QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(theAttacked->label);
    QGraphicsColorizeEffect* effect1 = new QGraphicsColorizeEffect(attacker->label);
    effect1->setColor(Qt::blue);
    attacker->label->setGraphicsEffect(effect1);
    //theAttacked受击效果
    effect->setColor(Qt::red);
    theAttacked->label->setGraphicsEffect(effect);
    QEventLoop loop00;
    QTimer::singleShot(800, &loop00, SLOT(quit()));
    loop00.exec();
    effect->setEnabled(false); // 禁用效果
    effect1->setEnabled(false);
}
void MyAnimation::performDead(worship*& w)
{
    w->label->setMovie(w->DeadMovie);

    // 连接frameChanged信号与槽函数
    QEventLoop loop;
    connect(w->DeadMovie, &QMovie::frameChanged, w->label, [&](int frameNumber){
        // 如果动画播放到最后一帧，停止动画
        if (frameNumber == w->AttackMovie->frameCount() - 1) {
            w->DeadMovie->stop(); // 停止动画
            // 动画播放完成后,初始化（结束）动画
            w->label->setMovie(nullptr);
            w->healthBar->setFixedSize(0,0);
            loop.quit();
        }
    });
    w->DeadMovie->start();

    // 等待动画播放完成
    loop.exec();
}

void MyAnimation::performDeadP(worship *&w)
{
    w->label->setPixmap(*w->eDeadPixmap);
    QEventLoop loop00;
    QTimer::singleShot(800, &loop00, SLOT(quit()));
    loop00.exec();
    w->label->clear();
    w->healthBar->setFixedSize(0,0);
}

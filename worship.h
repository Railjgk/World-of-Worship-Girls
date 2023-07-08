#ifndef WORSHIP_H
#define WORSHIP_H
#include<QLabel>
#include<QMovie>
#include<QTimer>
#include<QString>
#include<QDebug>
#include<QDir>
#include<QObject>
#include<QProgressBar>
#include <synchapi.h>

class worship;
class equipment{//装备 1战列主炮 2巡洋主炮 3驱逐主炮 4鱼雷 5轰炸机 6舰载机
public:
    equipment(int _kind,worship &ship);
    ~equipment();
    int atk;
    int hp;
    int speed;
    double shield;
    int kind;
    worship *p=nullptr;
    QLabel *label=nullptr;//装备图标，暂未初始化
    void arm(worship*& ship);
};


class worship
{
public:
    worship(QString _kind,QString _name);
    ~worship();
    QString kind;
    QString name;
    //int x,y;//初始位置
    int hp;//血量
    int atk;//炮击值
    int speed;//装填，值越大一回合中攻击次序越靠前
    double shield;//装甲，轻甲0.7 中甲1 重甲1.3，受到伤害为atk/shield extratk*shield
    bool ifsunk=false;//判断舰船是否沉没，沉没为true
    bool airdefense=false;//判断舰载机种类，战斗机为true（可防空）
    bool extratk=false;//判断是否有鱼雷攻击，true则在所有单位炮击结束后进行鱼雷攻击，顺序按各舰船speed计算
    equipment *equip=nullptr;//舰船装备 ////////无法实现，子类无法用父类指针
    QMovie *movie=nullptr;
    QString AttackPath;
    QString MovePath;
    QString DeadPath;
    QString StandPath;
    QString VictoryPath;
    QString TuozhuaiPath;
    QString eStandPath;
    QString eDeadPath;
    QMovie* AttackMovie;
    QMovie* MoveMovie;
    QMovie* StandMovie;
    QMovie* VictoryMovie;
    QMovie* DeadMovie;
    QMovie* TuozhuaiMovie;
    QPixmap* eStandPixmap;
    QPixmap* eDeadPixmap;

    QLabel *label=nullptr;
    QProgressBar* healthBar = nullptr;//血量条

    void Attack(worship*&p);
    void Extratk(worship*&p);
    void Hurt(double harm);
    void Victory();
    void Dead();

    void performStand();
public slots:
};


#endif // WORSHIP_H

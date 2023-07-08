#ifndef W_BATTLE_H
#define W_BATTLE_H

#include <QDialog>
#include<QString>
#include<QLabel>
#include <QApplication>
#include <QTimer>
#include <QGraphicsColorizeEffect>
#include<QProgressBar>
#include<QLayout>
#include<QMediaPlayer>
#include<QAudioOutput>
#include "myanimation.h"
#include"pause.h"

namespace Ui {
class w_battle;
}

//继承自对话框，开始新窗口
class w_battle : public QDialog
{
    Q_OBJECT

public:
    std::vector<worship*> ship[2];//我方和敌方(编号分别为0和1)
    int sum[2] = { 0 };//各有舰船数量
    bool stopAttack = 0;
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    //QLabel *member[2][6] = {{NULL}}; //战斗成员（用于表示gif图）
    //逻辑上的战舰用队列表示，便于删除死亡成员；ui上的战舰另设一个引用指针数组表示，因为位置固定。但无法关联啊，所以还是需要只用一个东西表示，插入时即确定位置

    void ship2ui(bool camp);
    void input(bool camp, int n = 0, std::vector<worship*> s = {nullptr});//输入我方和敌方数据
    void _input(int* a);
    int attack();//战斗算法,返回胜利者的阵营(0/1)，平局返回-1
    void resetBar();

    void setPictrue(QString s);
    void stopMusic();

    explicit w_battle(QWidget *parent = nullptr);
    ~w_battle();

signals:
    void signalAttack(worship*& attacker, worship*& theAttacked);//w_battle类中的播放攻击动画的信号，对应worship类中的performAttack槽

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::w_battle *ui;
};

#endif // W_BATTLE_H

/* 问题：需要多线程
 * 这个类只能负责修改处理鼠标事件
 * 相比之下，子线程应该
*/

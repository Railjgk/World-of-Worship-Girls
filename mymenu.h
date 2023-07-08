
#ifndef MYMENU_H
#define MYMENU_H

#include <QWidget>
#include <QMediaPlayer>
#include<QAudioOutput>
#include "levelselection.h"
#include "ui_levelselection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyMenu; }
QT_END_NAMESPACE

class MyMenu : public QWidget

{
    Q_OBJECT

public:
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    void stopMusic();
    MyMenu(QWidget *parent = nullptr);
    ~MyMenu();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::MyMenu *ui;
    levelselection* Levels;
signals:
    //用于让主程序接受的信号，待补充
    void readyforquit();
    void start();
    void dockyard();
};

#endif // MYMENU_H

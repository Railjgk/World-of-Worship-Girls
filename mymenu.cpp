
#include "mymenu.h"
#include "ui_mymenu.h"
#include "mypushbutton.h"
#include "levelselection.h"
#include <QMessageBox>
#include <QGuiApplication>
#include <QTimer>
#include <QDialog>

void MyMenu::stopMusic() {
    // 停止音乐播放
    player->stop();
    // 释放相关资源
    player->deleteLater();
    audioOutput->deleteLater();
}

MyMenu::MyMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyMenu)
{
    ui->setupUi(this);
    // 创建一个QMediaPlayer对象
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setSource(QUrl::fromLocalFile("../material/sound/menu.mp3"));
    audioOutput->setVolume(50);
    player->setLoops(-1); // 设置循环播放次数为无限循环（-1 表示无限循环）
    player->play();

    QPixmap background("../material/interface/menu.png");
    background = background.scaled(QSize(1280, 800), Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    this->setFixedSize(1280, 800);
    //配置主场景（大小，图片背景）
    //this->resize(800,600);
    //setFixedSize()可以设置为固定大小
    //获取屏幕尺寸
    QRect screen_geometry=QGuiApplication::primaryScreen()->availableGeometry();
    //获取窗口尺寸
    QRect widget_geometry=this->frameGeometry();
    //将窗口移动到屏幕中央
    int x=(screen_geometry.width()-widget_geometry.width())/2;
    int y=(screen_geometry.height()-widget_geometry.height())/2;
    this->move(x,y);

    //准备退出按钮（可以设置一个dialog，让玩家三思（doge））
    MyPushButton* quitBtn=new MyPushButton(true,"../material/quit.png");
    quitBtn->setParent(this);
    quitBtn->move((this->width()-quitBtn->width())*0.1,this->height()*0.2);
    connect(quitBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了退出";

        //目前只是为了功能的完整性简单实现了一下
        int flag=QMessageBox::question(this,tr("确认退出"),tr("你真的要退出吗？qwq"),QMessageBox::Yes,QMessageBox::No);
        if(flag==QMessageBox::Yes){
            close();
        }

    });

    //出击按钮
    MyPushButton* startBtn=new MyPushButton(true,"../material/start.png");
    startBtn->setParent(this);
    startBtn->move((this->width()-startBtn->width())*0.1,this->height()*0.7);
    connect(startBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了出击";

        stopMusic();
        //这里可以插入一个音效

        //延时进入选择关卡，才能看见弹跳的效果
        QTimer::singleShot(200,this,[=](){
            this->hide();//主场景隐藏
            Levels=new levelselection;//实例化选择关卡场景
            Levels->setGeometry(this->geometry());
            Levels->show();
        });

    });

}

MyMenu::~MyMenu()
{
    delete ui;
}

void MyMenu::closeEvent(QCloseEvent *event)
{
    stopMusic();
    QWidget::closeEvent(event);
}



#include "end.h"
#include "ui_end.h"
#include "mymenu.h"

void end::stopMusic()
{
    // 停止音乐播放
    player->stop();
    // 释放相关资源
    player->deleteLater();
    audioOutput->deleteLater();
}

end::end(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::end)
{
    ui->setupUi(this);
    setModal(true);
}


end::~end()
{
    delete ui;
}

void end::myshow(int winner)
{
    show();
    if(!winner){
        // 创建一个QMediaPlayer对象
        player = new QMediaPlayer(this);
        audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
        player->setSource(QUrl::fromLocalFile("../material/sound/victory_changchun.mp3"));
        audioOutput->setVolume(50);
        player->setLoops(1);
        player->play();

        ui->label->setText("恭喜，战斗胜利！");
        QPixmap background("../material/victory.jpg");
        background = background.scaled(QSize(300, 400), Qt::IgnoreAspectRatio);

        QPalette palette;
        palette.setBrush(QPalette::Window, background);
        this->setPalette(palette);

        this->setFixedSize(300, 400);
    }
    else{
        // 创建一个QMediaPlayer对象
        player = new QMediaPlayer(this);
        audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
        player->setSource(QUrl::fromLocalFile("../material/sound/dead_changchun.mp3"));
        audioOutput->setVolume(50);
        player->setLoops(1);
        player->play();

        ui->label->setText("战斗失败\nQAQ");
        QPixmap background("../material/fail.jpg");
        background = background.scaled(QSize(300, 400), Qt::IgnoreAspectRatio);

        QPalette palette;
        palette.setBrush(QPalette::Window, background);
        this->setPalette(palette);

        this->setFixedSize(300, 400);
    }
}

void end::closeEvent(QCloseEvent *event)
{
    stopMusic();
    MyMenu* m=new MyMenu;
    m->show();
    QDialog::closeEvent(event);
}

void end::on_pushButton_clicked()
{
    close();
}


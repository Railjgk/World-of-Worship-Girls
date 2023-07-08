#include "levelselection.h"
#include "ui_levelselection.h"
#include"Button_Ship.h"
#include"w_battle.h"
levelselection::levelselection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::levelselection)
{
    ui->setupUi(this);
    // 创建一个QMediaPlayer对象
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setSource(QUrl::fromLocalFile("../material/sound/levelselection.mp3"));
    audioOutput->setVolume(50);
    player->setLoops(-1); // 设置循环播放次数为无限循环（-1 表示无限循环）
    player->play();

    this->setWindowTitle("编队");
    Button_Ship *btn1=new Button_Ship(1,this);
    Button_Ship *btn2=new Button_Ship(2,this);
    Button_Ship *btn3=new Button_Ship(3,this);
    Button_Ship *btn4=new Button_Ship(4,this);
    btn1->setFocusPolicy(Qt::NoFocus);
    btn2->setFocusPolicy(Qt::NoFocus);
    btn3->setFocusPolicy(Qt::NoFocus);
    btn4->setFocusPolicy(Qt::NoFocus);


    btn1->move(90,400);
    btn2->move(390,400);
    btn3->move(690,400);
    btn4->move(990,400);

    QPixmap background("../material/interface/background_l.jpg");
    background = background.scaled(QSize(1280, 800), Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    this->setFixedSize(1280, 800);
}

levelselection::~levelselection()
{
    delete ui;
}

void levelselection::stopMusic()
{
    // 停止音乐播放
    player->stop();
    // 释放相关资源
    player->deleteLater();
    audioOutput->deleteLater();
}

void levelselection::closeEvent(QCloseEvent *event)
{
    stopMusic();
    QWidget::closeEvent(event);;
}


void levelselection::on_enter_battle_clicked()
{
    stopMusic();
    w_battle *bf=new w_battle;
    //注意：双方舰船指针不能指向相同
    //bf->_input(fleets);
    this->hide();
    for(int i=1;i<=4;++i)
        qDebug() << fleets[i] << ' ';
    qDebug()<< Qt::endl;
    worship* s[5]={nullptr};

    s[1] = new worship ("cruiser","chaijun");
    s[2] = new worship ("destroyer","changchun");
    s[3] = new worship ("battleship","changmen");
    s[4] = new worship ("aircraft","qiye");
    std::vector<worship*> _s;
    for(int i=1;i<=4;++i)
        _s.push_back(s[fleets[i]]);



    worship ship_1("qz_enemy","qz_enemy");
    worship ship_2("qz_enemy","qz_enemy");
    worship ship_3("qz_enemy","qz_enemy");
    //worship ship_4("destroyer","aisaikesi");
    std::vector<worship*> s2;
    s2.push_back(&ship_1);
    s2.push_back(&ship_2);
    //s2.push_back(&ship_3);
    //s2.push_back(&ship_4);
    end* myend = new end;
    bf->input(0,4,_s);
    bf->input(1,2,s2);
    bf->show();
    bf->setPictrue("../material/interface/background.jpg");

    bf->player = new QMediaPlayer(this);
    bf->audioOutput = new QAudioOutput;
    bf->player->setAudioOutput(audioOutput);
    bf->player->setSource(QUrl::fromLocalFile("../material/sound/battle1.mp3"));
    bf->audioOutput->setVolume(50);
    bf->player->setLoops(-1); // 设置循环播放次数为无限循环（-1 表示无限循环）
    bf->player->play();

    myend->myshow(bf->attack());
    bf->close();
}


void levelselection::on_pushButton_clicked()
{
    stopMusic();
    w_battle *bf=new w_battle;
    //注意：双方舰船指针不能指向相同
    //bf->_input(fleets);
    this->hide();
    for(int i=1;i<=4;++i)
        qDebug() << fleets[i] << ' ';
    qDebug()<< Qt::endl;
    worship* s[5]={nullptr};

    s[1] = new worship ("cruiser","chaijun");
    s[2] = new worship ("destroyer","changchun");
    s[3] = new worship ("battleship","changmen");
    s[4] = new worship ("aircraft","qiye");
    std::vector<worship*> _s;
    for(int i=1;i<=4;++i)
        _s.push_back(s[fleets[i]]);



    worship ship_1("zl_enemy","zl_enemy");
    worship ship_2("qz_enemy","qz_enemy");
    //worship ship_3("hm_enemy","hm_enemy");
    //worship ship_4("destroyer","aisaikesi");
    std::vector<worship*> s2;
    s2.push_back(&ship_1);
    s2.push_back(&ship_2);
    //s2.push_back(&ship_3);
    //s2.push_back(&ship_4);
    end* myend = new end;
    bf->input(0,4,_s);
    bf->input(1,2,s2);
    bf->show();

    bf->player = new QMediaPlayer(this);
    bf->audioOutput = new QAudioOutput;
    bf->player->setAudioOutput(audioOutput);
    bf->player->setSource(QUrl::fromLocalFile("../material/sound/battle2.mp3"));
    bf->audioOutput->setVolume(50);
    bf->player->setLoops(-1); // 设置循环播放次数为无限循环（-1 表示无限循环）
    bf->player->play();

    bf->setPictrue("../material/interface/background2.jpg");
    myend->myshow(bf->attack());
    bf->close();
}


void levelselection::on_pushButton_2_clicked()
{
    stopMusic();
    w_battle *bf=new w_battle;
    //注意：双方舰船指针不能指向相同
    //bf->_input(fleets);
    this->hide();
    for(int i=1;i<=4;++i)
        qDebug() << fleets[i] << ' ';
    qDebug()<< Qt::endl;
    worship* s[5]={nullptr};

    s[1] = new worship ("cruiser","chaijun");
    s[2] = new worship ("destroyer","changchun");
    s[3] = new worship ("battleship","changmen");
    s[4] = new worship ("aircraft","qiye");
    std::vector<worship*> _s;
    for(int i=1;i<=4;++i)
        _s.push_back(s[fleets[i]]);



    worship ship_1("zl_enemy","zl_enemy");
    worship ship_2("qz_enemy","qz_enemy");
    worship ship_3("hm_enemy","hm_enemy");
    worship ship_4("destroyer","aisaikesi");
    std::vector<worship*> s2;
    s2.push_back(&ship_1);
    s2.push_back(&ship_2);
    s2.push_back(&ship_3);
    //s2.push_back(&ship_4);
    end *myend = new end;
    bf->input(0,4,_s);
    bf->input(1,3,s2);
    bf->show();

    bf->player = new QMediaPlayer(this);
    bf->audioOutput = new QAudioOutput;
    bf->player->setAudioOutput(audioOutput);
    bf->player->setSource(QUrl::fromLocalFile("../material/sound/battle3.mp3"));
    bf->audioOutput->setVolume(50);
    bf->player->setLoops(-1); // 设置循环播放次数为无限循环（-1 表示无限循环）
    bf->player->play();

    bf->setPictrue("../material/interface/background3.jpg");
    myend->myshow(bf->attack());
    bf->close();
}


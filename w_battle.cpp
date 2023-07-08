#include "w_battle.h"
#include "qaudiooutput.h"
#include "ui_w_battle.h"

struct location{
    int x;
    int y;
};
location loca[2][6]={{{250,400},{250,200},{250,600},{50,400},{50,200},{50,600}},
                       {{830,400},{830,200},{830,600},{1030,400},{1030,200},{1030,600}}};


w_battle::w_battle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::w_battle)
{
    ui->setupUi(this);
    this->setWindowTitle("战斗界面");
    QPixmap background("../material/interface/background.jpg");
    background = background.scaled(QSize(1280, 800), Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    this->setFixedSize(1280, 800);
}

w_battle::~w_battle()
{
    delete ui;
}

void w_battle::closeEvent(QCloseEvent *event)
{
    stopAttack=1;
    QDialog::closeEvent(event);
}

//读入数据
void w_battle::ship2ui(bool camp)//使ui中的指针和类中的指针指向相同的位置，这样改变类中的成员也会造成ui界面中成员的改变
{
    if(!camp)
        switch (sum[camp]){
        case 6:ship[camp][5]->label=ui->label05;ship[camp][5]->healthBar=ui->progressBar05;
        case 5:ship[camp][4]->label=ui->label01;ship[camp][4]->healthBar=ui->progressBar01;
        case 4:ship[camp][3]->label=ui->label03;ship[camp][3]->healthBar=ui->progressBar03;
        case 3:ship[camp][2]->label=ui->label06;ship[camp][2]->healthBar=ui->progressBar06;
        case 2:ship[camp][1]->label=ui->label02;ship[camp][1]->healthBar=ui->progressBar02;
        case 1:ship[camp][0]->label=ui->label04;ship[camp][0]->healthBar=ui->progressBar04;
        }
    else
        switch (sum[camp]){
        case 6:ship[camp][5]->label=ui->label16;ship[camp][5]->healthBar=ui->progressBar16;
        case 5:ship[camp][4]->label=ui->label12;ship[camp][4]->healthBar=ui->progressBar12;
        case 4:ship[camp][3]->label=ui->label14;ship[camp][3]->healthBar=ui->progressBar14;
        case 3:ship[camp][2]->label=ui->label15;ship[camp][2]->healthBar=ui->progressBar15;
        case 2:ship[camp][1]->label=ui->label11;ship[camp][1]->healthBar=ui->progressBar11;
        case 1:ship[camp][0]->label=ui->label13;ship[camp][0]->healthBar=ui->progressBar13;
        }
}

void w_battle::input(bool camp, int n, std::vector<worship*> s) {
    sum[camp] = n;
    for (int i = 0; i < n; ++i) {
        ship[camp].push_back(s[i]);
    }

    ship2ui(camp);

    // 设置QLabel显示给定位置的gif图片 & 添加血条
    int i=0;
    for(i=0;i<n;++i){
        if(ship[camp][i]->StandMovie->isValid()){
        ship[camp][i]->label->setMovie(ship[camp][i]->StandMovie);
        ship[camp][i]->StandMovie->start();
        }
        else if(!ship[camp][i]->eStandPixmap->isNull()){
            ship[camp][i]->label->setPixmap(*ship[camp][i]->eStandPixmap);
        }
        ship[camp][i]->healthBar->resize(180,20);
        ship[camp][i]->healthBar->setMinimum(0);
        ship[camp][i]->healthBar->setMaximum(ship[camp][i]->hp); // 设置血量范围
        ship[camp][i]->healthBar->setValue(ship[camp][i]->hp); // 设置初始血量值
        //ship[camp][i]->setGeometry(loca[camp][i].x,loca[camp][i].y, 200, 200);
    }
}

void w_battle::_input(int* a)
{
    worship* s[4]={nullptr};
    for(int i=0;i<4;++i){
        switch (a[i]){
        case 1:s[0]=new worship("cruiser","chaijun");ship[0].push_back(s[0]);break;
        case 2:s[1]=new worship("destroyer","changchun");ship[0].push_back(s[1]);break;
        case 3:s[2]=new worship("battleship","changmen");ship[0].push_back(s[2]);break;
        case 4:s[3]=new worship("aircraft","qiye");ship[0].push_back(s[3]);break;
            }
    }
}

bool attackcmp(worship* w1, worship* w2) {
    return w1->speed < w2->speed;
}

int w_battle::attack() {
    //需在这里，show之后重新设置血条，因为之前血条的设置被ui布局界面限制
    resetBar();
    //ui->progressBar01->setFixedSize(0, 0);
    //形成延迟
    QEventLoop loop0;
    QTimer::singleShot(1000, &loop0, SLOT(quit()));
    loop0.exec();

    if(stopAttack)return -1;
    MyAnimation myani;
    //连接信号和槽
    //connect(this, SIGNAL(signalAttack(worship*&, worship*&)), &myani, SLOT(performAttack(worship*&, worship*&)));

    //最多进行十轮交火
    bool battleEnd = 0;
    std::vector<worship*> orderOfAttack[2];//进攻顺序,复制了双方舰船向量，但顺序不同
    int sumA[2];
    for (int camp = 0; camp < 2; ++camp) {
        orderOfAttack[camp] = ship[camp];
        sort(orderOfAttack[camp].begin(), orderOfAttack[camp].end(), attackcmp);
        sumA[camp]=sum[camp];
    }

    for (int i = 0; i <= 20 && !battleEnd; ++i) {
        setWindowOpacity(0.8);
        QString s = QString("第%1轮 炮击战").arg(i+1);
        ui->rounds->setText(s);
        //通过设置一下窗口透明度表明新一轮战斗
        QTimer::singleShot(250, &loop0, SLOT(quit()));
        loop0.exec();
        setWindowOpacity(0.9);
        QTimer::singleShot(250, &loop0, SLOT(quit()));
        loop0.exec();

        //空战和炮击，双方交替
        int curr[2] = { 0 };//记录当前应空战和炮击的舰船

        for (int j = 0; j < fmax(sum[0], sum[1]); ++j) { //进行fmax(sum[0], sum[1])次循环？？？？
            for (int camp = 0; camp < 2; ++camp) { //对于两个阵营
                for (; curr[camp] < sumA[camp]; ++curr[camp]) {
                    if(stopAttack)return -1;
                    if (!orderOfAttack[camp][curr[camp]] || orderOfAttack[camp][curr[camp]]->extratk)  //跳过空指针（由ship[camp]中被击沉战舰的delete造成）和鱼雷攻击的舰船
                        continue;


                    setWindowOpacity(1);
                    worship* attacker = orderOfAttack[camp][curr[camp]]; //当前指向的战舰
                    worship* theAttacked = ship[!camp][0];
                    ++curr[camp];
                    attacker->Attack(theAttacked);//攻击当前编号最靠前的敌方舰船


                    if(attacker->AttackMovie->isValid()) //只有能播放动画的才播放动画
                        // 触发播放动画
                        myani.performAttack(attacker, theAttacked);
                    else if(!attacker->eStandPixmap->isNull())//敌方类播放动画
                        myani.performAttackP(attacker, theAttacked);


                    if (theAttacked->ifsunk) {
                        //QTimer::singleShot(100, &loop0, SLOT(quit()));
                        //loop0.exec();
                        if(theAttacked->DeadMovie->isValid())
                            myani.performDead(theAttacked);
                        else if(!theAttacked->eDeadPixmap->isNull())
                            myani.performDeadP(theAttacked);
                        qDebug() << theAttacked->name << "deaded by " << attacker->name << Qt::endl;
                        for(auto i=orderOfAttack[!camp].begin();i!=orderOfAttack[!camp].end();++i) //将进攻序列中的被击沉战舰改为空指针
                            if(*i==theAttacked){
                                *i=NULL;break;
                            }
                        //没new不用delete//delete theAttacked;//删除被击沉战舰
                        ship[!camp].erase(ship[!camp].begin());
                        --sum[!camp];

                        if (sum[!camp] <= 0)
                            return camp;
                    }
                    break;
                }
            }
        }

        //鱼雷战///////////////需修改
        s = QString("第%1轮 鱼雷战").arg(i+1);
        ui->rounds->setText(s);
        QTimer::singleShot(500, &loop0, SLOT(quit()));
        loop0.exec();
        for (int camp = 0; camp < 2; ++camp) {
            setWindowOpacity(1);
            //std::vector<worship*[2]> orderOfExtratk;
            for (int j = 0; j < sumA[camp]; ++j) {
                if(stopAttack)return -1;
                worship* attacker = orderOfAttack[camp][j]; //当前指向的战舰
                worship* theAttacked = ship[!camp][0];
                if(!attacker||!attacker->extratk)continue; //跳过空指针和不能鱼雷攻击的舰船


                attacker->Extratk(theAttacked);

                    //orderOfExtratk.push_back({attacker,theAttacked});
                ////////////////
                if(attacker->AttackMovie->isValid()) //只有能播放动画的才播放动画
                    // 触发播放动画
                    myani.performAttack(attacker, theAttacked);
                else if(!attacker->eStandPixmap->isNull())//敌方播放动画
                    myani.performAttackP(attacker, theAttacked);


                if (theAttacked->ifsunk) {
                    QTimer::singleShot(100, &loop0, SLOT(quit()));
                    loop0.exec();
                    if(theAttacked->DeadMovie->isValid())
                        myani.performDead(theAttacked);
                    else if(!theAttacked->eDeadPixmap->isNull())
                        myani.performDeadP(theAttacked);

                    qDebug() << theAttacked->name << "deaded by " << attacker->name << Qt::endl;
                    for(auto k=orderOfAttack[!camp].begin();k!=orderOfAttack[!camp].end();++k) //将进攻序列中的被击沉战舰改为空指针
                        if(*k==theAttacked){
                            *k=NULL;break;
                        }
                    //delete theAttacked;
                    ship[!camp].erase(ship[!camp].begin());
                    --sum[!camp];

                    if (sum[!camp] <= 0)
                        return camp;
                }
            }

        }
    }
    return -1;
}

void w_battle::resetBar()
{
    ui->progressBar01->setFixedSize(0,0);
    ui->progressBar02->setFixedSize(0,0);
    ui->progressBar03->setFixedSize(0,0);
    ui->progressBar04->setFixedSize(0,0);
    ui->progressBar05->setFixedSize(0,0);
    ui->progressBar06->setFixedSize(0,0);
    ui->progressBar11->setFixedSize(0,0);
    ui->progressBar12->setFixedSize(0,0);
    ui->progressBar13->setFixedSize(0,0);
    ui->progressBar14->setFixedSize(0,0);
    ui->progressBar15->setFixedSize(0,0);
    ui->progressBar16->setFixedSize(0,0);
    for(int camp=0;camp<2;++camp)
        for(int i=0;i<sum[camp];++i)
            ship[camp][i]->healthBar->setFixedSize(180,20);
}

void w_battle::setPictrue(QString s)
{
    QPixmap background(s);
    background = background.scaled(QSize(1280, 800), Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
}

void w_battle::stopMusic()
{
    // 停止音乐播放
    player->stop();
    // 释放相关资源
    player->deleteLater();
    audioOutput->deleteLater();
}


//每方是按编号排列的，攻击也是按编队顺序
//分为两轮，空战炮击和鱼雷战

//播放一次就更换的功能由connect函数实现
//如何和战斗动画协调？




void w_battle::on_pushButton_clicked()
{
    QEventLoop loop;
        //得创建一个新窗口
    Pause*  pauseW= new Pause;
    pauseW->show();
    player->pause();

    //connect
    connect(pauseW,&Pause::dialogClosed,this,[&](){
        loop.quit();
        player->play();
    });
    connect(pauseW,&Pause::accepted,this,[&](){
        loop.quit();
        close();
    });
    loop.exec();
}



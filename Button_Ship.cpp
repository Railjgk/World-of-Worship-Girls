#include"Button_Ship.h"

#include<algorithm>
#include<QMovie>
extern int ifs=1;

extern int si=0,sj=0;//记录点击的按钮序号

int fleets[5]={0,1,2,3,4};//编队顺序
Button_Ship *btmp;//记录第一次点击的按钮

void swap(int i,int j){//对fleets数组进行交换
    if(i!=j)
    {
        //qDebug()<<"i:"<<i<<" j:"<<j;
        int tmp=fleets[i];
        fleets[i]=fleets[j];
        fleets[j]=tmp;

        //qDebug()<<"Swap called"<<Qt::endl;
        //qDebug()<<"i:"<<i<<" j:"<<j<<Qt::endl;
        /*for(int i=1;i<5;i++){
            qDebug()<<"fleets:"<<fleets[i];
        }*/
    }
    else{
        //qDebug()<<"equal"<<"i: "<<i<<Qt::endl;
    }
}
void Button_Ship::upload(){
    if(ifs==-1){
        si=n;
    }
    else{
        sj=n;
    }
    qDebug()<<"upload called";
}
void Button_Ship::change(){
    ifs*=-1;
    //qDebug()<<ifs;
}
void Button_Ship::Gif_change(){
    //qDebug()<<"Gif"<<n<<"called";
    if(ifs==-1){
        movie->stop();
        label->setMovie(mov);
        mov->start();
        //qDebug()<<"si:"<<si;
        btmp=this;
    }
    else{
        //qDebug()<<"sj:"<<sj<<" n:"<<n;
        mov->stop();
        swap(si,sj);
        switch(fleets[n]){
        case 1:{
            movie->setFileName("../material/chaijun/stand.gif");
            mov->setFileName("../material/chaijun/tuozhuai.gif");
            break;
        }
        case 2:{
            movie->setFileName("../material/changchun/stand.gif");
            mov->setFileName("../material/changchun/tuozhuai.gif");
            break;
        }
        case 3:{
            movie->setFileName("../material/changmen/stand.gif");
            mov->setFileName("../material/changmen/tuozhuai.gif");
            break;
        }
        case 4:{
            movie->setFileName("../material/qiye/stand.gif");
            mov->setFileName("../material/qiye/tuozhuai.gif");

            break;
        }
        }
        si=0;
        sj=0;

        if(n!=btmp->n){
            btmp->Gif_change();
        }

        label->setMovie(movie);
        movie->start();

        //qDebug()<<"n:"<<n<<movie->fileName();
        //qDebug()<<"n:"<<n<<mov->fileName();

    }
}

Button_Ship::Button_Ship(int _n,QWidget *parent):QPushButton(parent){
    n=_n;

    this->resize(QSize(200,200));
    this->setFlat(true);
    this->setStyleSheet("QPushButton{border:0px;}");
    vlayout= new QVBoxLayout();
    vlayout->addStretch(1);

    layout=new QHBoxLayout(this);
    layout->addStretch(1);

    label=new QLabel();
    label->setAlignment(Qt::AlignCenter);
    switch(fleets[n]){
    case 1:{
        movie=new QMovie("../material/chaijun/stand.gif");
        mov=new QMovie("../material/chaijun/tuozhuai.gif");
        break;
    }
    case 2:{
        movie=new QMovie("../material/changchun/stand.gif");
        mov=new QMovie("../material/changchun/tuozhuai.gif");
        break;
    }
    case 3:{
        movie=new QMovie("../material/changmen/stand.gif");
        mov=new QMovie("../material/changmen/tuozhuai.gif");
        break;
    }
    case 4:{
        movie=new QMovie("../material/qiye/stand.gif");
        mov=new QMovie("../material/qiye/tuozhuai.gif");
        break;
    }
    }
    movie->setScaledSize(QSize(200,200));
    mov->setScaledSize(QSize(200,200));
    label->setMovie(movie);
    layout->addWidget(label);
    movie->start();

    vlayout->addWidget(this);
    vlayout->addStretch(1);
    setLayout(vlayout);



    connect(this,&Button_Ship::clicked,this,&Button_Ship::change);
    connect(this,&Button_Ship::clicked,this,&Button_Ship::upload);
    connect(this,&Button_Ship::clicked,this,&Button_Ship::Gif_change);


}



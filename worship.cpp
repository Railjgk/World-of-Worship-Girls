#include "worship.h"

worship::worship(QString _kind,QString _name)
{
    kind=_kind;
    name=_name;
    AttackPath=":/material/"+name+"/attack.gif";
    MovePath=":/material/"+name+"/move.gif";
    StandPath=":/material/"+name+"/stand.gif";
    VictoryPath=":/material/"+name+"/victory.gif";
    DeadPath=":/material/"+name+"/dead.gif";
    TuozhuaiPath=":/material/"+name+"/tuozhuai.gif";
    if(kind=="destroyer"){
        hp=1000;
        atk=100;
        speed=40;
        shield=0.7;
        equipment(3,*this);
    }
    if(kind=="cruiser"){
        hp=2000;
        atk=200;
        speed=30;
        shield=1;
        equipment(2,*this);
    }
    if(kind=="battleship"){
        hp=3000;
        atk=300;
        speed=20;
        shield=1.3;
        equipment(1,*this);
    }
    if(kind=="aircraft"){//需实现两种舰载机切换
        hp=3000;
        atk=300;
        speed=20;
        shield=1.3;
        equipment(5,*this);
    }

}
equipment::equipment(int _kind,worship &ship){
    kind=_kind;
    p=&ship;
    ship.equip=this;
    switch(_kind){
    case 1:{
        atk=300;
        hp=0;
        speed=-10;
        shield=0;
        break;
    }
    case 2:{
        atk=200;
        hp=0;
        speed=0;
        shield=0;
        break;
    }
    case 3:{
        atk=100;
        hp=0;
        speed=10;
        shield=0;
        break;
    }
    case 4:{//鱼雷的伤害单独用atk计算
        atk=500;
        hp=0;
        speed=0;
        shield=0;
        p->extratk=true;
        break;
    }
    case 5:{
        atk=300;
        hp=0;
        speed=40;
        shield=0;
        break;
    }
    case 6:{
        atk=0;
        hp=0;
        speed=0;
        shield=0;
        p->airdefense=true;
        break;
    }
    }
    if(kind!=4)
    {
        p->atk+=atk;//装备给舰船提供属性加成
        p->hp+=hp;
        p->speed+=speed;
        p->shield+=shield;
    }


}
equipment::~equipment(){
    if(kind==6){
        p->airdefense=false;
    }
    if(kind!=4)
    {
        p->atk-=atk;//减去属性加成
        p->hp-=hp;
        p->speed-=speed;
        p->shield-=shield;
    }
    else{
        p->extratk=false;
    }
    p->equip=nullptr;
    p=nullptr;
}//可能的bug：多次析构导致舰船属性降低
void equipment::arm(worship &ship){
    p=&ship;
    ship.equip=this;
    switch(kind){
    case 1:{
        atk=300;
        hp=0;
        speed=-10;
        shield=0;
        break;
    }
    case 2:{
        atk=200;
        hp=0;
        speed=0;
        shield=0;
        break;
    }
    case 3:{
        atk=100;
        hp=0;
        speed=10;
        shield=0;
        break;
    }
    case 4:{//鱼雷的伤害单独用atk计算
        atk=500;
        hp=0;
        speed=0;
        shield=0;
        p->extratk=true;
        break;
    }
    case 5:{
        atk=300;
        hp=0;
        speed=40;
        shield=0;
        break;
    }
    case 6:{
        atk=0;
        hp=0;
        speed=0;
        shield=0;
        p->airdefense=true;
        break;
    }
    }
    if(kind!=4)
    {
        p->atk+=atk;//装备给舰船提供属性加成
        p->hp+=hp;
        p->speed+=speed;
        p->shield+=shield;
    }
}
void worship::Hurt(double hurt){//均需添加动画 hurt attack
    hp-=hurt;
    if(hp<=0){
        ifsunk=true;
    }
}
void worship::Attack(worship &p){
    double n=atk/p.shield;
    p.Hurt(n);//调用被攻击对象的Hurt函数
}
void worship::Extratk(worship &p,bool extra){//鱼雷攻击
    double n=atk*p.shield;
    p.Hurt(n);
}
void worship::Victory(){//后续补充舰船胜利动作
    qDebug()<<"victory\n";
}
void worship::Dead(){
    qDebug()<<"failed\n";
}



#include "mypushbutton.h"
#include <QPixmap>

MyPushButton::MyPushButton(bool mask,QString normalImg,QString pressedImg)
    :normalImgPath(normalImg),pressedImgPath(pressedImg)
{

    QPixmap pixmap;
    //加载图片
    bool ret=pixmap.load(normalImgPath);
    if(!ret){
        qDebug()<<normalImg<<"this image failed to load!";
    }
    else {
        qDebug()<<normalImg<<"this image loads successfully!";
    }

    //调整按钮的大小
    this->setFixedSize(pixmap.width(),pixmap.height());
    //设置遮罩
    if(mask)
        this->setMask(pixmap.mask());
    //设置无边框
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置按钮图像
    this->setIcon(pixmap);
    //设置图像大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void MyPushButton::zoom1(){
    //创建动画对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);
    //创建开始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation->setEndValue(QRect(this->x(),this->y()+20,this->width(),this->height()));
    //设置缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation->start();
}

void MyPushButton::zoom2(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+20,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

}

void MyPushButton::enterEvent(QEvent*e){
    if(hoverImgPath!=""){
    //鼠标进入按钮时，将按钮的样式设置为hoverImg
        setStyleSheet(hoverImgPath);
    }
    QPushButton::enterEvent(dynamic_cast<QEnterEvent*>(e));
}

void MyPushButton::leaveEvent(QEvent*e){
    if(hoverImgPath!=""){
    //鼠标离开按钮时，将按钮的样式设置为normalImg
        setStyleSheet(normalImgPath);
    }
    QPushButton::leaveEvent(e);

}

void MyPushButton::mousePressEvent(QMouseEvent*e){
    if(pressedImgPath!=""){
    //鼠标按下时，将按钮的样式设置为pressedImg
        setStyleSheet(pressedImgPath);
    }
    else
        move(x()+1,y()+1);
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent*e){
    if(hoverImgPath!=""){
        //鼠标释放按钮时，将按钮的样式表重制为hoverImg或者normalImg
        if(rect().contains(e->pos()))
           setStyleSheet(hoverImgPath);
        else
           setStyleSheet(normalImgPath);
    }
    else
        move(x()-1,y()-1);
    QPushButton::mouseReleaseEvent(e);
}

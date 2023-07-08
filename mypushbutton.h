
#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H


#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QWidget>
#include <QPropertyAnimation>
#include <QMouseEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(bool mask,QString normalImg,QString pressedImg="");
protected:
    void enterEvent(QEvent*e);
    void leaveEvent(QEvent*e);
    void mousePressEvent(QMouseEvent*e);
    void mouseReleaseEvent(QMouseEvent*e);

private:
    //按钮在默认状态下的样式
    QString normalImgPath;
    //鼠标悬停在按钮上的样式
    QString hoverImgPath;
    //鼠标按下时按钮的样式
    QString pressedImgPath;
signals:

public slots:
    //按钮向下移动10像素
    void zoom1();
    //按钮向上移动10像素
    void zoom2();
};

#endif // MYPUSHBUTTON_H

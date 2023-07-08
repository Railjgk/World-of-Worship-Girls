#pragma once
#ifndef BUTTON_SHIP_H
#define BUTTON_SHIP_H

#include<QPushButton>
#include<QLabel>
#include<vector>
#include<QDialog>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QDebug>
#include"worship.h"
extern int fleets[5];

class Button_Ship:public QPushButton{
    Q_OBJECT
public:
    int n;
    QVBoxLayout *vlayout;
    QHBoxLayout *layout;
    QLabel *label;
    QMovie *movie;
    QMovie *mov;
    Button_Ship(int _n,QWidget *parent=nullptr);

signals:

public slots:
    void change();
    void upload();
    void Gif_change();
};
void swap(int i,int j);

#endif // BUTTON_SHIP_H

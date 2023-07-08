#ifndef LEVELSELECTION_H
#define LEVELSELECTION_H

#include <QWidget>
#include <end.h>
#include<QMediaPlayer>
#include<QAudioOutput>

namespace Ui {
class levelselection;
}

class levelselection : public QWidget
{
    Q_OBJECT

public:
    explicit levelselection(QWidget *parent = nullptr);
    ~levelselection();
    Ui::levelselection *ui;
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    void stopMusic();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:

    void on_enter_battle_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
};

#endif // LEVELSELECTION_H

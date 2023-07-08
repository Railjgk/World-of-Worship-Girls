#ifndef END_H
#define END_H

#include <QDialog>
#include<QMediaPlayer>
#include<QAudioOutput>

namespace Ui {
class end;
}

class end : public QDialog
{
    Q_OBJECT

public:
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    void stopMusic();
    explicit end(QWidget *parent = nullptr);
    ~end();

    void myshow(int winner);
protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::end *ui;
};

#endif // END_H

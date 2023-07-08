#ifndef PAUSE_H
#define PAUSE_H

#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QPalette>

namespace Ui {
class Pause;
}

class Pause : public QDialog
{
    Q_OBJECT

public:
    explicit Pause(QWidget *parent = nullptr);
    ~Pause();
signals:
    void dialogClosed();

protected:
    void closeEvent(QCloseEvent* event) override;
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Pause *ui;
};

#endif // PAUSE_H

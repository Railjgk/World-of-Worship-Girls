#include "pause.h"
#include "ui_pause.h"

Pause::Pause(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pause)
{
    ui->setupUi(this);
    setModal(true);
    QPalette palette_l = ui->label->palette();
    palette_l.setColor(QPalette::WindowText, Qt::white);
    ui->label->setPalette(palette_l);

    QPixmap background("../material/pause.png");
    background = background.scaled(QSize(600, 500), Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    this->setFixedSize(600, 500);
}

Pause::~Pause()
{
    delete ui;
}

void Pause::closeEvent(QCloseEvent *event)
{
    emit dialogClosed();
    QDialog::closeEvent(event);
}



void Pause::on_buttonBox_accepted()
{
    close();
}


void Pause::on_buttonBox_rejected()
{
    emit dialogClosed();
    close();
}

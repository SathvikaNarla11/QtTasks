#include "scdialog.h"
#include "ui_scdialog.h"
#include <QTimer>

scDialog::scDialog(Overlay *ref, QWidget *parent)
    : QDialog(parent)
    , oscObj(ref)
    , ui(new Ui::scDialog)
{
    ui->setupUi(this);
}

scDialog::~scDialog()
{
    delete ui;
}

void scDialog::setImage(QPixmap pixmap)
{
    ui->label->setPixmap(pixmap);
}

void scDialog::mousePressEvent(QMouseEvent *event)
{
    // qDebug()<<event->pos();
    int num;

    bool openFrame = false;

    QPixmap img(":/Images/twitter.png");
    QPoint clickPoint = event->pos();

    QRect rect1(70, 152, 110, 108);
    QRect rect2(238, 152, 110, 108);
    QRect rect3(410, 152, 110, 108);
    QRect rect4(578, 152, 110, 108);


    if(rect1.contains(clickPoint))
    {
        num = 1;
        qDebug()<<"Yes1";
        openFrame = true;

    }
    else if(rect2.contains(clickPoint))
    {
        num = 2;
        qDebug()<<"Yes2";
        openFrame = true;
    }
    else if(rect3.contains(clickPoint))
    {
        num = 3;
        qDebug()<<"Yes3";
        openFrame = true;
    }
    else if(rect4.contains(clickPoint))
    {
        num = 4;
        qDebug()<<"Yes4";
        openFrame = true;
    }
    fb = new Frame(num, this);

    connect(fb, &Frame::iconSelected, this, [=](const QPixmap &pixmap, const QString &iconName, int labelNum){
        qDebug()<<"From scdialog"<<pixmap;
        qDebug()<<"From scdialog"<<iconName;
        qDebug()<<"From scdialog"<<labelNum;
        oscObj->setIconInLabelWithName(pixmap, iconName, labelNum);  // custom new function
        QTimer::singleShot(100, this, &QWidget::close);
    });

    if(openFrame)
    {
        fb->show();
    }
}


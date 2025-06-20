#include "optiondialog.h"
#include "ui_optiondialog.h"
#include <QDebug>

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mousePressEvent : "<<event->pos();
}

void OptionDialog::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"mouseMoveEvent : "<<event->pos();
}

void OptionDialog::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"mouseReleaseEvent : "<<event->pos();
}

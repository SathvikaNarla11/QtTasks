#include "frame.h"
#include "ui_frame.h"
#include <QStandardItemModel>

Frame::Frame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::Frame)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    QStandardItemModel *model = new QStandardItemModel();

    QIcon icon1(":/Images/apple.png");
    QIcon icon2(":/Images/reddit.png");
    QIcon icon3(":/Images/twitter.png");
    QIcon icon4(":/Images/visual-basic.png");

    QStandardItem *item1 = new QStandardItem(icon1, "");
    QStandardItem *item2 = new QStandardItem(icon2, "");
    QStandardItem *item3 = new QStandardItem(icon3, "");
    QStandardItem *item4 = new QStandardItem(icon4, "");

    model->appendRow(item1);
    model->appendRow(item2);
    model->appendRow(item3);
    model->appendRow(item3);

    ui->listView->setModel(model);
    ui->listView->setIconSize(QSize(45,45));
    ui->listView->setSpacing(6);

}

Frame::~Frame()
{
    delete ui;
}

void Frame::on_pushButtonCloseListView_clicked()
{
    close();
}


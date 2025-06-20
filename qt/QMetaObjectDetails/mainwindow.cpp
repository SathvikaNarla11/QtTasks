#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QObject* obj = new QPushButton("Click me");

    // const QMetaObject* meta = obj->metaObject();

    // qDebug() << "Class name:" << meta->className();
    // qDebug() << "Number of methods:" << meta->methodCount();
    // qDebug() << "Number of properties:" << meta->propertyCount();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QObject *obj = ui->pushButton;
    const QMetaObject *meta = obj->metaObject();

    qDebug() << " Class name : "<<meta->className();
    qDebug() << "Number of methods:" << meta->methodCount();
    qDebug() << "Number of properties:" << meta->propertyCount();
    // qDebug() << meta->
}






















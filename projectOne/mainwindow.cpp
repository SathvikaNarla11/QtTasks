#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    // connect(timer, SIGNAL(timeout()), this, SLOT(myfunction()));
    // timer->start(2000);
    connect(ui->pushBtn, SIGNAL(clicked()), this, SLOT(myfunction()),Qt::DirectConnection);



    ui->comboBox->insertItem(0, "Choose from below");
    ui->comboBox->addItem("1");
    ui->comboBox->addItems({"2","3","4"});
    ui->comboBox->insertItem(5, "Hello");
    ui->comboBox->insertItems(6, {"ONE", "TWO"});

    QStringList items;
    items << "Three" << "Four" << "Five";
    ui->comboBox->insertItems(7, items);

    QStringList moreitems = {"5", "6", "7"};
    ui->comboBox->insertItems(8, moreitems);

    ui->comboBox->setItemText(4, "Changed to FOUR");

    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::myfunOne);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(myfunTwo()));
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::myfunThree);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunOne()
{
    ui->label->show();
}

void MainWindow::myfunTwo()
{
    ui->label_2->show();
}

void MainWindow::myfunThree()
{
    ui->label_3->show();
}

void MainWindow::myfunction()
{
    qDebug()<<"Push button clicked!";
    // secdialog sd;
    // sd.setModal(true);
    // sd.exec();
    obj = new secdialog();
    obj->open();
    QTimer::singleShot(5000, obj, &QDialog::accept);
}


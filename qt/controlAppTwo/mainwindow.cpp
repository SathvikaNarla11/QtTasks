#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QEventLoop>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objOverlay = new Overlay();

    connect(ui->pushButtonOptions, &QPushButton::clicked, this, &MainWindow::openOverlay);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: openOverlay()
{
    qDebug()<<"1. Open overlay clicked";

    objOverlay->exec();
}

void MainWindow::on_pushButtonSC_clicked()
{
    qDebug()<<"Shortcut clicked";

    scObj = new scDialog(objOverlay, this);
    QPixmap overlayPixmap = objOverlay->grab();
    scObj->setImage(overlayPixmap);

    // QEventLoop loop;
    scObj->exec();
    // loop.exec();

    qDebug()<<"Shortcut closed";
}

// void MainWindow::on_pushButtonSC_clicked()
// {
//     qDebug() << "Shortcut clicked";

//     scObj = new scDialog(objOverlay, this);
//     QPixmap overlayPixmap = objOverlay->grab();
//     scObj->setImage(overlayPixmap);

//     QEventLoop loop;
//     QObject::connect(scObj, &QDialog::finished, &loop, &QEventLoop::quit);
//     scObj->open();
//     loop.exec();  // ⏳ Wait here until dialog closes

//     qDebug() << "Dialog closed, now continue";
// }




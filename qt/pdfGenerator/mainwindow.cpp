#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPdfDocument>
#include <QPdfView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushBtnGenerate, &QPushButton::clicked, this, &MainWindow::generatePdfFun);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generatePdfFun()
{
    qDebug()<<"Generating PDF..";

    QPdfDocument *doc = new QPdfDocument;
    doc->load("C:/qtworkfolder/qt/pdfGenerator/7.pdf"); // Make sure this file exists in your working directory

    QPdfView *view = new QPdfView;
    view->setDocument(doc);
    view->resize(1000, 800);
    view->show();

}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Member variable
QFrame* overlayList = nullptr;

void MainWindow::setupOverlayList() {
    // Create a frameless popup-style widget
    overlayList = new QFrame(this, Qt::Popup);
    overlayList->setFrameShape(QFrame::Box);
    overlayList->setStyleSheet("background-color: white; border: 1px solid gray;");

    QVBoxLayout* layout = new QVBoxLayout(overlayList);
    layout->setContentsMargins(10, 10, 10, 10);

    // Add example list items (you can use buttons, labels, or icons)
    for (int i = 0; i < 5; ++i) {
        QPushButton* item = new QPushButton(QString("Item %1").arg(i + 1));
        layout->addWidget(item);

        // Connect item click if needed
        connect(item, &QPushButton::clicked, [=]() {
            qDebug() << "Clicked item" << i + 1;
            overlayList->hide();  // Optional auto-hide
        });
    }

    overlayList->setLayout(layout);
    overlayList->adjustSize();
}

// On pushButton click
void MainWindow::on_pushButton_clicked() {
    if (!overlayList) {
        setupOverlayList();
    }

    // Position the overlay below the button
    QPoint btnPos = ui->pushButton->mapToGlobal(QPoint(0, ui->pushButton->height()));
    overlayList->move(btnPos);
    overlayList->show();
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "overlay.h"
#include "scdialog.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Overlay *objOverlay;
    scDialog *scObj;

public slots:
    void openOverlay();

private slots:
    void on_pushButtonSC_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

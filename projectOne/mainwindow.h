#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <secdialog.h>
#include <QTimer>

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

public slots:
    void myfunction();
    void myfunOne();
    void myfunTwo();
    void myfunThree();

private slots:
    // void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    secdialog *obj;
    QTimer *timer;
};
#endif // MAINWINDOW_H

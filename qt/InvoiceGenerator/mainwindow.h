#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include "qtablewidget.h"
#include <QMainWindow>
#include <QTableWidget>

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

    // QTableWidget *tableWidget;

    QMap<QString, double> itemsCost;

    // QLineEdit *lineEditUnitPrice;

public slots:
    void saveTableToPdf();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonDel_clicked();
    // void updateLineEditUnitPrice();
    void updateUnitPrice(const QString &cashierName, QLineEdit *lineEditUnitPrice, QLineEdit *lineEditQuantity);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

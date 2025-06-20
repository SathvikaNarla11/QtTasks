#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMap>
#include <QLabel>
#include <QSettings>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QPushButton *selectBtn;
    QMap<QString, QLabel*> iconAssignment;
    QMap<QLabel*, QString> labelIcons;

public slots:
    void openListView();
    void listEventClicked(const QModelIndex &index);
    void closeEvent(QCloseEvent *event);
    QString getIconPath(const QString &iconName);

private slots:
    void on_pushButtonCloseIcon_clicked();

private:
    Ui::Dialog *ui;
    QTimer *autoHideTimer = nullptr;
};

#endif // DIALOG_H

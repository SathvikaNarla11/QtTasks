#ifndef OVERLAY_H
#define OVERLAY_H

#include <QDialog>
#include "frame.h"
#include <QLabel>
#include <QSettings>

namespace Ui {
class Overlay;
}

class Overlay : public QDialog
{
    Q_OBJECT

public:
    explicit Overlay(QWidget *parent = nullptr);
    ~Overlay();

    Frame *fObj;

    QMap<QString, QLabel*> iconAssignment;  // iconName → label
    QMap<QLabel*, QString> labelIcons;      // label → iconName

public slots:
    void listViewShow(int num);
    void setIconInLabelWithName(const QPixmap&, const QString&, int);
    void closeEvent(QCloseEvent *event);
    QString getIconPath(const QString &iconName);

signals:
    void iconSelected(const QPixmap&, const QString&, int);

private:
    Ui::Overlay *ui;
};

#endif // OVERLAY_H

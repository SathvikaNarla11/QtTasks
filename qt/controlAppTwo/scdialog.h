#ifndef SCDIALOG_H
#define SCDIALOG_H

#include <QDialog>
#include "frame.h"
#include "overlay.h"
#include <QMouseEvent>

namespace Ui {
class scDialog;
}

class scDialog : public QDialog
{
    Q_OBJECT

public:
    explicit scDialog(Overlay *ref ,QWidget *parent = nullptr);
    ~scDialog();

    Frame *fb;
    Overlay *oscObj;


public slots:
    void setImage(QPixmap pixmap);

    void mousePressEvent(QMouseEvent *event);

private:
    Ui::scDialog *ui;
};

#endif // SCDIALOG_H

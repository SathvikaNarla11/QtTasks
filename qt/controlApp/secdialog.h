#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include "frame.h"

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

    Frame *fObj;

public slots:
    void on_pushButton_clicked();

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H

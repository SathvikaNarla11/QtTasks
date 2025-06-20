#include "secdialog.h"
#include "ui_secdialog.h"

SecDialog::SecDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SecDialog)
{
    ui->setupUi(this);

    QPixmap pix(":/Images/DesignImg.jfif");
    ui->label->setPixmap(pix.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_clicked()
{
    fObj = new Frame();
    fObj->show();
}

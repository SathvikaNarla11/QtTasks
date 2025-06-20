#include "overlay.h"
#include "ui_overlay.h"
#include <QDebug>

Overlay::Overlay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Overlay)
{
    ui->setupUi(this);

    connect(ui->pushButton1, &QPushButton::clicked, this, [=](){
        listViewShow(1);
    });
    connect(ui->pushButton2, &QPushButton::clicked, this, [=](){
        listViewShow(2);
    });
    connect(ui->pushButton3, &QPushButton::clicked, this, [=](){
        listViewShow(3);
    });
    connect(ui->pushButton4, &QPushButton::clicked, this, [=](){
        listViewShow(4);
    });


    QSettings settings("Company", "App");

    QMap<QString, QLabel*> keyToLabel =
    {
        {"label1Icon", ui->label1},
        {"label2Icon", ui->label2},
        {"label3Icon", ui->label3},
        {"label4Icon", ui->label4}
    };

    for(auto it = keyToLabel.begin(); it != keyToLabel.end(); ++it)
    {
        QString iconName = settings.value(it.key()).toString();

        if(!iconName.isEmpty())
        {
            QString path = getIconPath(iconName);
            QPixmap pixmap(path);
            it.value()->setPixmap(pixmap.scaled(91, 91, Qt::KeepAspectRatio));
            labelIcons[it.value()] = iconName;
            iconAssignment[iconName] = it.value();
        }
    }
}

Overlay::~Overlay()
{
    delete ui;
}

void Overlay :: listViewShow(int num)
{
    qDebug()<<"2. Open listView clicked";
    fObj = new Frame(num, this);

    connect(fObj, &Frame::iconSelected, this, [=](const QPixmap &pixmap, const QString &iconName, int labelNum){
        setIconInLabelWithName(pixmap, iconName, labelNum);  // custom new function
    });

    fObj->show();
}

void Overlay::setIconInLabelWithName(const QPixmap &pixmap, const QString &iconName, int labelNum)
{
    qDebug()<<"Invoked";
    qDebug()<<"From Overlay"<<pixmap;
    qDebug()<<"From Overlay"<<iconName;
    qDebug()<<"From Overlay"<<labelNum;
    QLabel *targetLabel = nullptr;
    if (labelNum == 1) targetLabel = ui->label1;
    else if (labelNum == 2) targetLabel = ui->label2;
    else if (labelNum == 3) targetLabel = ui->label3;
    else if (labelNum == 4) targetLabel = ui->label4;
    else return;

    // If icon already assigned to another label, clear it
    if (iconAssignment.contains(iconName)) {
        QLabel *oldLabel = iconAssignment[iconName];
        if (oldLabel != targetLabel) {
            oldLabel->clear();
            labelIcons.remove(oldLabel);
        }
    }

    // Remove previous icon from this label (if any)
    for (auto it = iconAssignment.begin(); it != iconAssignment.end(); ) {
        if (it.value() == targetLabel)
            it = iconAssignment.erase(it);
        else
            ++it;
    }

    targetLabel->setPixmap(pixmap.scaled(targetLabel->size(), Qt::KeepAspectRatio));
    iconAssignment[iconName] = targetLabel;
    labelIcons[targetLabel] = iconName;
}

void Overlay :: closeEvent(QCloseEvent *event)
{
    QSettings settings("Company", "App");

    settings.setValue("label1Icon", labelIcons[ui->label1]);
    settings.setValue("label2Icon", labelIcons[ui->label2]);
    settings.setValue("label3Icon", labelIcons[ui->label3]);
    settings.setValue("label4Icon", labelIcons[ui->label4]);

    QDialog::closeEvent(event);
}

QString Overlay :: getIconPath(const QString &iconName)
{
    if(iconName == "Icon1") return ":/Images/apple.png";
    if(iconName == "Icon2") return ":/Images/reddit.png";
    if(iconName == "Icon3") return ":/Images/twitter.png";
    if(iconName == "Icon4") return ":/Images/visual-basic.png";
    return "";
}











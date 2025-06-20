#include "dialog.h"
#include "ui_dialog.h"
#include <QStandardItemModel>
#include <QTimer>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Overlay");

    // ui->listView->hide();
    ui->frame->hide();

    connect(ui->pushButtonB1, &QPushButton::clicked, this, &Dialog::openListView);
    connect(ui->pushButtonB2, &QPushButton::clicked, this, &Dialog::openListView);
    connect(ui->pushButtonB3, &QPushButton::clicked, this, &Dialog::openListView);

    QSettings settings("YourCompany", "YourApp");

    QMap<QString, QLabel*> keyToLabel = {
        {"label1Icon", ui->label1},
        {"label2Icon", ui->label2},
        {"label3Icon", ui->label3}
    };

    for (auto it = keyToLabel.begin(); it != keyToLabel.end(); ++it) {
        QString iconName = settings.value(it.key()).toString();

        if (!iconName.isEmpty()) {
            QString path = getIconPath(iconName);  // Helper function below
            QPixmap pixmap(path);
            it.value()->setPixmap(pixmap.scaled(48, 48, Qt::KeepAspectRatio));
            labelIcons[it.value()] = iconName;
            iconAssignment[iconName] = it.value(); // maintain the unique constraint
        }
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog:: openListView()
{
    selectBtn = qobject_cast<QPushButton *>(sender());
    qDebug()<<"sb : "<<selectBtn;

    QStandardItemModel *model = new QStandardItemModel(this);

    QIcon icon1(":/new/prefix1/Icons/apple.png");
    QIcon icon2(":/new/prefix1/Icons/reddit.png");
    QIcon icon3(":/new/prefix1/Icons/twitter.png");
    QIcon icon4(":/new/prefix1/Icons/visual-basic.png");

    QStandardItem *item1 = new QStandardItem(icon1, "Icon1");
    QStandardItem *item2 = new QStandardItem(icon2, "Icon2");
    QStandardItem *item3 = new QStandardItem(icon3, "Icon3");
    QStandardItem *item4 = new QStandardItem(icon4, "Icon4");

    model->appendRow(item1);
    model->appendRow(item2);
    model->appendRow(item3);
    model->appendRow(item4);

    ui->listView->setModel(model);
    // ui->listView->setViewMode(QListView::IconMode);
    ui->listView->setViewMode(QListView::ListMode);
    // ui->listView->show();
    ui->listView->setIconSize(QSize(48, 48)); // Ensure consistent icon size
    ui->listView->setSpacing(8);              // Optional spacing between items
    ui->listView->setMovement(QListView::Static); // Prevents dragging/reordering

    ui->frame->show();

    if (!autoHideTimer) {
        autoHideTimer = new QTimer(this);
        autoHideTimer->setSingleShot(true);
        connect(autoHideTimer, &QTimer::timeout, this, [this]() {
            if (ui->frame->isVisible()) {
                ui->frame->close();
                qDebug() << "Frame hidden after timeout";
            }
        });
    }

    autoHideTimer->start(5000);

    connect(ui->listView, &QListView::clicked, this, &Dialog::listEventClicked);
}


void Dialog:: listEventClicked(const QModelIndex &index)
{
    qDebug()<<"LIST EVENT CLICKED";
    qDebug()<<ui->listView->model();
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->listView->model());
    qDebug()<<model;

    QStandardItem *item = model->itemFromIndex(index);

    QString iconName = item->text();  // e.g., "apple", "twitter", etc.
    QPixmap pixmap = item->icon().pixmap(QSize(48, 48));

    QLabel *targetLabel = nullptr;

    if (selectBtn == ui->pushButtonB1)
        targetLabel = ui->label1;
    else if (selectBtn == ui->pushButtonB2)
        targetLabel = ui->label2;
    else if (selectBtn == ui->pushButtonB3)
        targetLabel = ui->label3;

    if (!targetLabel)
        return;

    if (iconAssignment.contains(iconName)) {
        QLabel *conflictingLabel = iconAssignment[iconName];
        if (conflictingLabel != targetLabel) {
            conflictingLabel->clear();  // remove pixmap
            labelIcons.remove(conflictingLabel);
        }
    }
    targetLabel->setPixmap(pixmap);
    labelIcons[targetLabel] = iconName;

    for (auto it = iconAssignment.begin(); it != iconAssignment.end(); ) {
        if (it.value() == targetLabel)
            it = iconAssignment.erase(it);
        else
            ++it;
    }

    iconAssignment[iconName] = targetLabel;

    // ui->listView->hide();
    ui->frame->hide();
}

void Dialog::closeEvent(QCloseEvent *event)
{
    QSettings settings("YourCompany", "YourApp");

    // Save current icon names assigned to each label
    settings.setValue("label1Icon", labelIcons[ui->label1]);
    settings.setValue("label2Icon", labelIcons[ui->label2]);
    settings.setValue("label3Icon", labelIcons[ui->label3]);

    QDialog::closeEvent(event);
}

QString Dialog::getIconPath(const QString &iconName)
{
    if (iconName == "Icon1") return ":/new/prefix1/Icons/apple.png";
    if (iconName == "Icon2") return ":/new/prefix1/Icons/reddit.png";
    if (iconName == "Icon3") return ":/new/prefix1/Icons/twitter.png";
    if (iconName == "Icon4") return ":/new/prefix1/Icons/visual-basic.png";
    return "";
}

void Dialog::on_pushButtonCloseIcon_clicked()
{
    ui->frame->close();
}


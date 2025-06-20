#include "frame.h"
#include "ui_frame.h"
#include <QStandardItemModel>

// Frame::Frame(QWidget *parent)
Frame::Frame(int num, QWidget *parent)
    : QFrame(parent), ui(new Ui::Frame)
    , m_callerButtonNum(num)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    QIcon icon1(":/Images/apple.png");
    QIcon iconEmpty("");
    QIcon icon2(":/Images/reddit.png");
    QIcon icon3(":/Images/twitter.png");
    QIcon icon4(":/Images/visual-basic.png");

    QStandardItemModel *model = new QStandardItemModel(this);

    QStandardItem *item1 = new QStandardItem(icon1, "Icon1");
    QStandardItem *item2 = new QStandardItem(icon2, "Icon2");
    QStandardItem *item3 = new QStandardItem(icon3, "Icon3");
    QStandardItem *item4 = new QStandardItem(icon4, "Icon4");

    for (QStandardItem *item : {item1, item2, item3, item4})
    {
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        // QStandardItem *itemEmpty = new QStandardItem(iconEmpty, "");
        model->appendRow(new QStandardItem(iconEmpty, ""));
        model->appendRow(new QStandardItem(iconEmpty, ""));
        model->appendRow(item);
        model->appendRow(new QStandardItem(iconEmpty, ""));
        model->appendRow(new QStandardItem(iconEmpty, ""));
    }

    ui->listView->setModel(model);
    ui->listView->setViewMode(QListView::IconMode);
    ui->listView->setIconSize(QSize(47, 47));
    ui->listView->setGridSize(QSize(60, 80));

    connect(ui->listView, &QListView::clicked, this, &::Frame::listViewClicked);
}

Frame::~Frame()
{
    delete ui;
}

void Frame::listViewClicked(const QModelIndex &index)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->listView->model());
    QStandardItem *item = model->itemFromIndex(index);

    QString iconName = item->text();  // Important!
    QPixmap pixmap = item->icon().pixmap(QSize(48, 48));

    emit iconSelected(pixmap, iconName, m_callerButtonNum);  // Now sends iconName too
    this->close();
}

void Frame::on_pushButton_clicked()
{
    this->close();
}










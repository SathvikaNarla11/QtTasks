#ifndef FRAME_H
#define FRAME_H

#include <QFrame>

namespace Ui {
class Frame;
}

class Frame : public QFrame
{
    Q_OBJECT

public:
    explicit Frame(int num, QWidget *parent = nullptr);
    ~Frame();

signals:
    void iconSelected(const QPixmap &pixmap, const QString &iconName, int labelNum);

public slots:
    void listViewClicked(const QModelIndex &index);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Frame *ui;
    int m_callerButtonNum;
};

#endif // FRAME_H

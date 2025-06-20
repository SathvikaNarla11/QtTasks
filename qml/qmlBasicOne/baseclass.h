#ifndef BASECLASS_H
#define BASECLASS_H

#include <QObject>
#include <QDebug>

class baseclass : public QObject
{
    Q_OBJECT
public:
    explicit baseclass(QObject *parent = nullptr);
    Q_INVOKABLE void funDisplay();

public slots:
    void myfun();

signals:

};

#endif // BASECLASS_H

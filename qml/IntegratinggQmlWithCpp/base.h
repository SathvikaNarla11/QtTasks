#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QDebug>

class Base : public QObject
{
    Q_OBJECT
public:
    explicit Base(QObject *parent = nullptr);

signals:

public slots:
    Q_INVOKABLE void display();

};

#endif // BASE_H

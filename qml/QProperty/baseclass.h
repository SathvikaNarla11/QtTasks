#ifndef BASECLASS_H
#define BASECLASS_H

#include <QObject>
#include <QDebug>

class baseclass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged FINAL)

public:
    explicit baseclass(QObject *parent = nullptr);

int value() const
    {
    qDebug()<<"value() is called";
    return m_value;
    }

void setValue(int v)
    {
    qDebug()<<"m_value 1 : "<<m_value;
        m_value = v;
    qDebug()<<"m_value 2 : "<<m_value;
    //     qDebug()<<"v : "<<v;
    // m_value = v;
    // if(v != m_value)
    //     {
    //         m_value = v;
    //         emit valueChanged();
    //     }
    }

private:
    int m_value = 66;

signals:
    void valueChanged();

};

#endif // BASECLASS_H

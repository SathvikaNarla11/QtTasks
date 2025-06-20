#include "base.h"

Base::Base(QObject *parent)
    : QObject{parent}
{
    qDebug()<<"Base constructor";

}

void Base::display()
{
    qDebug()<<"Display from base invoked";
}

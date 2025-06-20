#include "baseclass.h"

baseclass::baseclass(QObject *parent)
    : QObject{parent}
{}

void baseclass::funDisplay()
{
    qDebug()<<"Display function from baseclass";
}

void baseclass::myfun()
{
    qDebug()<<"myfun() is called";
}

#ifndef DASHBOARDSERVICES_H
#define DASHBOARDSERVICES_H

#include <QObject>
#include <QTimer>

class DashboardServices : public QObject
{
    Q_OBJECT

public:
    explicit DashboardServices(QObject *parent = nullptr);

    int speed() const;
    int rpm() const;
    int fuel() const;
    int temperature() const;

signals:
    void dataUpdated(int speed, int rpm, int fuel, int temperature);

private slots:
    void updateData();

private:
    QTimer m_timer;
    int m_speed = 0;
    int m_rpm = 0;
    int m_fuel = 100;
    int m_temp = 60;

    bool m_increasing = true;

};

#endif // DASHBOARDSERVICES_H





// #ifndef DASHBOARDSERVICES_H
// #define DASHBOARDSERVICES_H

// class DashboardServices
// {
// public:
//     DashboardServices();
// };

// #endif // DASHBOARDSERVICES_H




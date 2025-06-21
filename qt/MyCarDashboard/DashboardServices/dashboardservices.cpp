// #include "dashboardservices.h"

// DashboardServices::DashboardServices() {}


#include "dashboardservices.h"
#include <QRandomGenerator>

DashboardServices::DashboardServices(QObject *parent)
    : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &DashboardServices::updateData);
    m_timer.start(100); // Update every 1 second
}

void DashboardServices::updateData()
{
    // Simulate gradual speed changes
    if (m_increasing)
        m_speed += QRandomGenerator::global()->bounded(2, 4); // step up by 2–5
    else
        m_speed -= QRandomGenerator::global()->bounded(2, 4); // step down by 2–5

    if (m_speed >= 100) m_increasing = false;
    if (m_speed <= 0) m_increasing = true;

    // Clamp
    m_speed = qBound(0, m_speed, 100);

    // Simulate RPM roughly proportional to speed
    m_rpm = m_speed / 10;

    // Fuel reduces slowly
    m_fuel = qMax(0, m_fuel - 1);

    // Temp fluctuates slightly around 70–95
    m_temp += QRandomGenerator::global()->bounded(-1, 2); // -1, 0, or 1
    m_temp = qBound(70, m_temp, 95);

    emit dataUpdated(m_speed, m_rpm, m_fuel, m_temp);
}

int DashboardServices::speed() const       { return m_speed; }
int DashboardServices::rpm() const         { return m_rpm; }
int DashboardServices::fuel() const        { return m_fuel; }
int DashboardServices::temperature() const { return m_temp; }

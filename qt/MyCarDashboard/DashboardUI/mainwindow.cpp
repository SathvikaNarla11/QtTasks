#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customdial.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DashboardServices *service = new DashboardServices(this);

    // Create the CustomDial and insert it into the speedometerwidget
    CustomDial* speedometer = new CustomDial(this);
    speedometer->setGaugeType(CustomDial::GaugeType::Speedometer);
    speedometer->setRange(0, 100);
    speedometer->setNeedleColor(Qt::red);
    speedometer->setStep(10);
    speedometer->setPointColor(Qt::darkCyan);
    speedometer->setUnitLabel("MPH");
    ui->speedwidgetVL->addWidget(speedometer);

    CustomDial *tachometer = new CustomDial(this);
    tachometer->setGaugeType(CustomDial::GaugeType::Tachometer);
    tachometer->setRange(0, 9);
    tachometer->setNeedleColor(Qt::red);
    tachometer->setPointColor(Qt::darkCyan);
    tachometer->setStep(1);
    tachometer->setUnitLabel("X1000 \n RPM");
    ui->tachometerVL->addWidget(tachometer);

    CustomDial *fuelGauge = new CustomDial(this);
    fuelGauge->setGaugeType(CustomDial::GaugeType::Fuel);
    ui->fuelwidgetVL->addWidget(fuelGauge);

    CustomDial *tempGauge = new CustomDial(this);
    tempGauge->setGaugeType(CustomDial::GaugeType::Temp);
    ui->engTempwidgetVL->addWidget(tempGauge);


    connect(service, &DashboardServices::dataUpdated, this, [=](int speed, int rpm, int fuel, int temp){

        qDebug()<<"speed "<<speed;


        speedometer->setValue(speed);
        tachometer->setValue(rpm);
        fuelGauge->setValue(fuel);
        tempGauge->setValue(temp);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}
































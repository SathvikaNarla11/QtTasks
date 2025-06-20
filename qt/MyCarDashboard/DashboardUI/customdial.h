#ifndef CUSTOMDIAL_H
#define CUSTOMDIAL_H

#include <QWidget>


// CustomDial.h
// #pragma once
#include <QWidget>
#include <QColor>
#include <qpen.h>

class CustomDial : public QWidget {
    Q_OBJECT
public:
    explicit CustomDial(QWidget *parent = nullptr);

    void setValue(int value);                // Set current dial value
    void setRange(int min, int max);         // Set min and max values
    void setStep(int step);                  // Step between ticks
    void setUnitLabel(const QString &label); // E.g., "MPH"
    void setLabelFont(const QFont &font);
    void setNeedleColor(const QColor &color);
    void setCirclePen(const QPen &outer, const QPen &inner);
    void setNeedleLengthRatio(float ratio);
    void setTextColor(const QColor &color);
    void setAngleRange(int startAngle, int spanAngle);
    void setPointColor(const QColor &color);

    void drawOuterCircle(QPainter &painter, const QPoint &center, int outerRadius);
    void drawInnerCircle(QPainter &painter, const QPoint &center, int innerRadius);
    void drawTicksAndLabels(QPainter &painter, const QPoint &center, int innerRadius);
    void drawNeedle(QPainter &painter, const QPoint &center, int innerRadius);
    void drawCenterDot(QPainter &painter, const QPoint &center);
    void drawUnitLabel(QPainter &painter, int w, int h, int outerRadius);
    void drawMainTickAndLabel(QPainter &painter, const QPoint &center, int innerRadius, int value, double angle);
    void drawShortTick(QPainter &painter, const QPoint &center, int innerRadius, double angle);

    void setDrawOnlyOuterCircle(bool enable);
    void setFuelGauge(bool enable);

    void drawFuelTicksAndLabels(QPainter& painter, const QPoint& center, int innerRadius,
                                const QString& leftLabel, const QString& rightLabel,
                                const QVector<QColor>& tickColors);


    enum class GaugeType {
        None,
        Speedometer,
        Tachometer,
        Fuel,
        Temp
    };
    GaugeType m_gaugeType = GaugeType::None;
    void setGaugeType(GaugeType type);




protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_value = 0;
    int m_min; // = 0;
    int m_max; // = 100;
    int m_step = 10;
    QString m_unitLabel = "";
    QFont m_labelFont;
    QColor m_textColor = Qt::white;
    QColor m_needleColor; // = Qt::red;
    QColor m_pointColor; // = Qt::green;
    QPen m_outerCirclePen = QPen(QColor("#000020"), 6);
    QPen m_innerCirclePen = QPen(Qt::darkCyan, 6);
    float m_needleLengthRatio = 0.65f;
    int m_startAngle = 210;
    int m_spanAngle = 270;

    bool m_drawOnlyOuterCircle = false;
    bool m_isFuelGauge = false;

    double m_redArcStartAngle = -1;
    double m_redArcEndAngle = -1;
};

// class CustomDial : public QWidget
// {
//     Q_OBJECT
// public:
//     explicit CustomDial(QWidget *parent = nullptr);
//     void setSpeed(int mph);
//     QFont font;

// protected:
//     void paintEvent(QPaintEvent* event) override;

// private:
//     int m_speed;

// signals:
// };

#endif // CUSTOMDIAL_H


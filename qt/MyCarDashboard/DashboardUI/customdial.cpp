// CustomDial.cpp
#include "CustomDial.h"
#include <QPainter>
#include <QtMath>

CustomDial::CustomDial(QWidget *parent)
    : QWidget(parent) {
    m_labelFont.setBold(true);
    m_labelFont.setPointSize(15);
}

void CustomDial::setValue(int value) {
    m_value = qBound(m_min, value, m_max);
    update();
}
void CustomDial::setRange(int min, int max)
{
    m_min = min;
    m_max = max;
    update();
}
void CustomDial::setStep(int step)
{
    m_step = step;
    update();
}
void CustomDial::setUnitLabel(const QString &label)
{
    m_unitLabel = label;
    update();
}
void CustomDial::setLabelFont(const QFont &font)
{
    m_labelFont = font;
    update();
}
void CustomDial::setNeedleColor(const QColor &color)
{ m_needleColor = color;
    update();
}
void CustomDial::setPointColor(const QColor &color)
{
    m_pointColor = color;
    update();
}
void CustomDial::setCirclePen(const QPen &outer, const QPen &inner)
{
    m_outerCirclePen = outer;
    m_innerCirclePen = inner;
    update();
}
void CustomDial::setNeedleLengthRatio(float ratio)
{
    m_needleLengthRatio = ratio;
    update();
}
void CustomDial::setTextColor(const QColor &color)
{
    m_textColor = color;
    update();
}
void CustomDial::setAngleRange(int startAngle, int spanAngle)
{
    m_startAngle = startAngle;
    m_spanAngle = spanAngle;
    update();
}
void CustomDial::setDrawOnlyOuterCircle(bool enable) {
    m_drawOnlyOuterCircle = enable;
    update(); // Refresh the widget
}
void CustomDial::setFuelGauge(bool enable) {
    m_isFuelGauge = enable;
    update();
}

void CustomDial::setGaugeType(GaugeType type) {
    m_gaugeType = type;
    update();
}



void CustomDial::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width() + 8;
    int h = height() + 8;
    QPoint center(w / 2, h / 2);
    int outerRadius = qMin(w, h) / 2 - 20;
    int innerRadius = outerRadius * 0.95;

    if(m_drawOnlyOuterCircle)
    {
        drawOuterCircle(painter, center, outerRadius);
        return;
    }

    drawOuterCircle(painter, center, outerRadius);
    drawInnerCircle(painter, center, innerRadius);
    drawTicksAndLabels(painter, center, innerRadius);
    drawNeedle(painter, center, innerRadius);
    drawCenterDot(painter, center);
    drawUnitLabel(painter, w, h, outerRadius);

    if (m_gaugeType == GaugeType::Fuel || m_gaugeType == GaugeType::Temp) {
        drawOuterCircle(painter, center, outerRadius);

        QVector<QColor> colors;
        if (m_gaugeType == GaugeType::Fuel) {
            colors = { Qt::red, Qt::red, Qt::red, Qt::darkCyan, Qt::darkCyan, Qt::darkCyan, Qt::darkCyan, Qt::darkCyan, Qt::darkCyan, Qt::darkCyan, Qt::darkCyan, Qt::darkCyan };
            drawFuelTicksAndLabels(painter, center, innerRadius, "E", "F", colors);
        } else if (m_gaugeType == GaugeType::Temp) {
            colors = { Qt::darkCyan, Qt::darkCyan, Qt::darkCyan, Qt::darkCyan, Qt::darkCyan, Qt::darkCyan, Qt::yellow, Qt::yellow, Qt::red, Qt::red, Qt::red};
            drawFuelTicksAndLabels(painter, center, innerRadius, "C", "H", colors);
        }

        drawNeedle(painter, center, innerRadius);
        return;
    }

    if (m_gaugeType == GaugeType::Tachometer)
    {
        int arcRadius = innerRadius - 40;
        QRectF arcRect(center.x() - arcRadius, center.y() - arcRadius,
                       2 * arcRadius, 2 * arcRadius);

        QPen arcPen(Qt::red);
        arcPen.setWidth(4);
        painter.setPen(arcPen);

        // Qt draws clockwise — so we must go from end to start
        int startAngle16 = static_cast<int>(m_redArcEndAngle * 16);
        int spanAngle16 = static_cast<int>((m_redArcStartAngle - m_redArcEndAngle) * 16);
        painter.drawArc(arcRect, startAngle16, spanAngle16);
    }
}

void CustomDial::drawOuterCircle(QPainter& painter, const QPoint& center, int radius) {
    painter.setBrush(Qt::black);
    painter.setPen(m_outerCirclePen);
    painter.drawEllipse(center, radius, radius);
}

void CustomDial::drawInnerCircle(QPainter& painter, const QPoint& center, int radius) {
    painter.setBrush(Qt::black);
    painter.setPen(m_innerCirclePen);
    painter.drawEllipse(center, radius, radius);
}


void CustomDial::drawTicksAndLabels(QPainter& painter, const QPoint& center, int innerRadius) {
    int range = m_max - m_min;
    int numSteps = range / m_step;

    for (int i = 0; i <= numSteps; ++i) {
        int value = i * m_step;
        double angle = m_startAngle - (i * 30);  // Consider parameterizing `30`

        drawMainTickAndLabel(painter, center, innerRadius, value, angle);

        if (i < numSteps) {
            drawShortTick(painter, center, innerRadius, angle - 15);
        }
    }
}

void CustomDial::drawMainTickAndLabel(QPainter &painter, const QPoint &center, int innerRadius, int value, double angle) {
    double rad = qDegreesToRadians(angle);

    QPointF p1 = center + QPointF(innerRadius * 0.85 * qCos(rad), -innerRadius * 0.85 * qSin(rad));
    QPointF p2 = center + QPointF(innerRadius * qCos(rad), -innerRadius * qSin(rad));

    QPen pen(m_pointColor);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawLine(p1, p2);

    if (value == 6) {
        m_redArcStartAngle = angle;
    }
    if (value == 9) {
        m_redArcEndAngle = angle;
    }

    QPointF textPt;
    if(m_gaugeType == GaugeType::Speedometer)
    {
        textPt = center + QPointF((innerRadius - 40) * qCos(rad), -(innerRadius - 40) * qSin(rad));
    }
    else if(m_gaugeType == GaugeType::Tachometer)
    {
        textPt = center + QPointF((innerRadius - 60) * qCos(rad), -(innerRadius - 60) * qSin(rad));
    }
    painter.setPen(m_textColor);
    painter.setFont(m_labelFont);
    painter.drawText(QRectF(textPt.x() - 15, textPt.y() - 10, 33, 20), Qt::AlignCenter, QString::number(value));
    // If the value is 6 7 8 9, draw an arc from 6 to 9

}

void CustomDial::drawShortTick(QPainter &painter, const QPoint &center, int innerRadius, double angle) {
    double radShort = qDegreesToRadians(angle);

    QPointF p1Short = center + QPointF(innerRadius * 0.93 * qCos(radShort), -innerRadius * 0.93 * qSin(radShort));
    QPointF p2Short = center + QPointF(innerRadius * qCos(radShort), -innerRadius * qSin(radShort));

    QPen pen(m_pointColor);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawLine(p1Short, p2Short);
}

void CustomDial::drawFuelTicksAndLabels(QPainter& painter, const QPoint& center, int innerRadius,
                                        const QString& leftLabel, const QString& rightLabel,
                                        const QVector<QColor>& tickColors)
{
    int numTicks = tickColors.size(); // Use color count as tick count
    double startAngle = 150;
    double spanAngle = 125;

    for (int i = 0; i < numTicks; ++i) {
        double angle = startAngle - (i * (spanAngle / (numTicks - 1)));
        double rad = qDegreesToRadians(angle);

        QPointF p1 = center + QPointF(innerRadius * 0.88 * qCos(rad), -innerRadius * 0.88 * qSin(rad));
        QPointF p2 = center + QPointF(innerRadius * qCos(rad), -innerRadius * qSin(rad));

        QPen pen(tickColors[i]);
        pen.setWidth(5);
        painter.setPen(pen);
        painter.drawLine(p1, p2);
    }

    // Labels (E/F or C/H)
    painter.setPen(Qt::white);
    painter.setFont(m_labelFont);

    QPointF leftPos = center + QPointF((innerRadius - 0) * qCos(qDegreesToRadians(startAngle)),
                                       -(innerRadius - 40) * qSin(qDegreesToRadians(startAngle)));
    QPointF rightPos = center + QPointF((innerRadius - 0) * qCos(qDegreesToRadians(startAngle - spanAngle)),
                                        -(innerRadius - 40) * qSin(qDegreesToRadians(startAngle - spanAngle)));

    painter.drawText(QRectF(leftPos.x() - 10, leftPos.y() - 10, 20, 20), Qt::AlignCenter, leftLabel);
    painter.drawText(QRectF(rightPos.x() - 10, rightPos.y() - 10, 20, 20), Qt::AlignCenter, rightLabel);
}

void CustomDial::drawNeedle(QPainter& painter, const QPoint& center, int innerRadius) {
    int range = m_max - m_min;
    double valueAngle = m_startAngle - ((m_value - m_min) / float(range)) * m_spanAngle;
    double rad = qDegreesToRadians(valueAngle);

    QPointF needleEnd = center + QPointF(innerRadius * m_needleLengthRatio * qCos(rad), -innerRadius * m_needleLengthRatio * qSin(rad));

    painter.setPen(QPen(m_needleColor, 4));
    painter.drawLine(center, needleEnd);
}

void CustomDial::drawCenterDot(QPainter& painter, const QPoint& center) {
    painter.setBrush(m_needleColor);
    painter.drawEllipse(center, 5, 5);
}

void CustomDial::drawUnitLabel(QPainter& painter, int w, int h, int outerRadius) {
    if (!m_unitLabel.isEmpty()) {
        painter.setPen(m_textColor);
        painter.setFont(m_labelFont);
        painter.drawText(QRect(0, h / 2 + (outerRadius - 40) / 2, w, 60), Qt::AlignHCenter, m_unitLabel);
    }
}



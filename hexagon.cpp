#include "hexagon.h"
#include "qpainter.h"
#include "qpen.h"
#include <Cmath>

Hexagon::Hexagon()
{
    IsFilled = false;
    setAcceptHoverEvents(true);
}

Hexagon::Hexagon(QPointF point) : center(point)
{
   QPolygonF hexagon;
   for (int i = 0; i < 6; ++i) {
       qreal angle_deg = 60 * i - 30;
       qreal angle_rad = M_PI / 180 * angle_deg;
       QPointF point(center.x() + hexSize * cos(angle_rad),
                     center.y() + hexSize * sin(angle_rad));
       hexagon << point;
   }
    polygon = new QGraphicsPolygonItem(hexagon);
    polygon->setPen(QPen(Qt::black, 1));
    polygon->setBrush(QBrush(Qt::white));
    polygon->setZValue(3);
    IsFilled = false;
    setAcceptHoverEvents(true);
}

QGraphicsPolygonItem* Hexagon::getPOlygon() {
   return polygon;
}

QPointF Hexagon::getCenter() {
   return center;
}

bool Hexagon::contains(const QPointF &point) const
{
    return polygon->polygon().containsPoint(point, Qt::OddEvenFill);
}

QRectF Hexagon::boundingRect() const
{
    return polygon->boundingRect();
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (IsFilled) {
        painter->setBrush(QBrush(Qt::green));
    } else {
        painter->setBrush(polygon->brush());
    }
    painter->drawPolygon(polygon->polygon());
}

void Hexagon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    polygon->setPen(QPen(Qt::yellow, 3));
    polygon->setZValue(4);
    update();
}

void Hexagon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    polygon->setPen(QPen(Qt::black));
    polygon->setZValue(3);
    update();
}

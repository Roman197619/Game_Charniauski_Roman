#ifndef HEXAGON_H
#define HEXAGON_H

#include <QGraphicsPolygonItem>

class Hexagon : public QGraphicsPolygonItem
{
public:
   Hexagon();
   Hexagon(QPointF);

   int weight = 1;

   //void setColor(QColor);
   bool contains(const QPointF &point) const override;
   QGraphicsPolygonItem* getPOlygon();
   QPointF getCenter();

   QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
   bool IsFilled;

private:
   QGraphicsPolygonItem* polygon;
   QPointF center;

   int hexSize = 70;

};

#endif // HEXAGON_H

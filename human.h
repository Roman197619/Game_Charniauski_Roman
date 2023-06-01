#ifndef HUMAN_H
#define HUMAN_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QVariantAnimation>

class Human : public QObject, public QGraphicsItem
{
public:
    explicit Human(QObject *parent = nullptr);
    ~Human();

   QPointF getCenter() {return centr;}

   int legSize;
   int armSize;
   int bodySize;
   std::pair<double, double> headSize;
   QPointF centr;
  double arm1angle;
  double arm2angle;
  double leg1angle;
  double leg2angle;

QGraphicsPixmapItem* arm1;
QGraphicsPixmapItem* arm2;
QGraphicsPixmapItem* leg1;
QGraphicsPixmapItem* leg2;
QGraphicsPixmapItem* body;
QGraphicsPixmapItem* head;

void setCentr(QPointF);

  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  void addToScene(QGraphicsScene* scene);
void animation(QPainterPath path);
void walkAnimation();
void paintWalkingMan(QGraphicsScene *scene, int steps) {}
void moveAlongPath(QPainterPath path);
void moveCenterAlongPath(const QPainterPath &path);

bool inAnimation = false;
QVariantAnimation getAnimation() {return animation_; }
private slots:
    void updateAnimation();
    void updatePosition(const QVariant &value);
private:

    QVariantAnimation *animation_ = nullptr;
  double  maxArmAngle = 40.0;
   double maxLegAngle = 30.0;
 double armAngleStep1 = 4.0;
  double  legAngleStep1 = 3.0;
  double armAngleStep2 = 4.0;
   double  legAngleStep2 = 3.0;
    QTimer *animationTimer;
};


#endif // HUMAN_H


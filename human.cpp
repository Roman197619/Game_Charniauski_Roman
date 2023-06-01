

#include "human.h"
#include "qgraphicsview.h"
#include <QGraphicsLineItem>
#include <cmath>
#include <QVariantAnimation>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <iostream>
#include <random>

Human::Human(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
   animationTimer = new QTimer(this);
      connect(animationTimer, &QTimer::timeout, this, &Human::updateAnimation);
    animationTimer->start(50);
    centr = {100, 200};
       bodySize = 30;
    legSize = 1.5 * bodySize;
    armSize = 0.7 * legSize;
    headSize = {20,25};
    arm1angle = -40;
     arm2angle=  40;
     leg1angle=  30;
    leg2angle =  -30;

arm1 = new QGraphicsPixmapItem();
arm2 = new QGraphicsPixmapItem();
leg1 = new QGraphicsPixmapItem();
leg2 = new QGraphicsPixmapItem();
body = new QGraphicsPixmapItem();
head = new QGraphicsPixmapItem();

    this->setZValue(100);
QImage image1(armSize, 5, QImage::Format_ARGB32);
image1.fill(Qt::black);
QImage image2(armSize, 5, QImage::Format_ARGB32);
image2.fill(Qt::blue);
QImage image3(legSize, 5, QImage::Format_ARGB32);
image3.fill(Qt::yellow);
QImage image4(legSize, 5, QImage::Format_ARGB32);
image4.fill(Qt::green);

QImage image5(headSize.first, headSize.second, QImage::Format_ARGB32);
QPainter painter(&image5);
painter.setBrush(Qt::black);
painter.drawEllipse(0, 0, headSize.first, headSize.second);
painter.end();

QImage image6(bodySize, 5.
              , QImage::Format_ARGB32);
image6.fill(Qt::black);

    arm1->setPixmap(QPixmap::fromImage(image1));
    arm2->setPixmap(QPixmap::fromImage(image2));
    leg1->setPixmap(QPixmap::fromImage(image3));
    leg2->setPixmap(QPixmap::fromImage(image4));
    head->setPixmap(QPixmap::fromImage(image5));
    body->setPixmap(QPixmap::fromImage(image6));
    body->setRotation(90);

    arm1->setZValue(10);
    arm2->setZValue(10);
   leg1->setZValue(10);
   leg2->setZValue(10);
   body->setZValue(10);
   head->setZValue(10);
}

void Human::addToScene(QGraphicsScene* scene) {
   scene->addItem(arm1);
   scene->addItem(arm2);
   scene->addItem(leg1);
   scene->addItem(leg2);
   scene->addItem(body);
   scene->addItem(head);
}
Human::~Human()
{
}

void Human::setCentr(QPointF newCentr) {
   centr = newCentr;
}


void Human::updateAnimation()
{
    arm1angle += armAngleStep1;
    arm2angle -= armAngleStep2;
    if (arm1angle > maxArmAngle || arm1angle < -maxArmAngle)
        armAngleStep1 = -armAngleStep1;
    if (arm2angle > maxArmAngle || arm2angle < -maxArmAngle)
        armAngleStep2 = -armAngleStep2;

    leg1angle += legAngleStep1;
    leg2angle -= legAngleStep2;
    if (leg1angle > maxLegAngle || leg1angle < -maxLegAngle)
        legAngleStep1 = -legAngleStep1;
    if (leg2angle > maxLegAngle || leg2angle < -maxLegAngle)
        legAngleStep2 = -legAngleStep2;


                arm1->setPos(centr.x() , centr.y()  - bodySize / 2);
                arm1->setRotation(arm1angle + 90);

                arm2->setPos(centr.x() , centr.y()  - bodySize / 2);
                arm2->setRotation(arm2angle + 90);

                leg1->setPos(centr.x() , centr.y() +  bodySize / 2);
                leg1->setRotation(leg1angle + 90);

                leg2->setPos(centr.x() , centr.y() + bodySize / 2);
                leg2->setRotation(leg2angle + 90);

                body->setPos(centr.x(), centr.y() - bodySize / 2);
                head->setPos(centr.x() - headSize.first / 2, centr.y() - bodySize / 2 - headSize.second);

    update();
}

void Human::walkAnimation()
{
    int interval = 100;
    animationTimer->start(interval);
}

void Human::moveCenterAlongPath(const QPainterPath &path)
{
   inAnimation = true;
   animation_ = new QVariantAnimation(this);
   animation_->setDuration(700 * path.elementCount());
   animation_->setStartValue(centr);
   for (int i = 0; i < path.elementCount(); ++i) {
       QPointF point = path.elementAt(i);
       animation_->setKeyValueAt((qreal)i / (qreal)path.elementCount(), point);
   }
   animation_->setEndValue(path.pointAtPercent(1));
//   animation->setEasingCurve(QEasingCurve::InOutQuad);
   connect(animation_, &QVariantAnimation::valueChanged, this, &Human::updatePosition);

   animation_->start(QAbstractAnimation::DeleteWhenStopped);
   inAnimation = false;
}

void Human::updatePosition(const QVariant &value)
{
    QPointF pos = value.toPointF();
    setCentr(pos);
    updateAnimation();
}

void Human::animation(QPainterPath path)
{

}

QRectF Human::boundingRect() const
{
    return QRectF(centr.x() - armSize, centr.y() - bodySize / 2 - legSize, centr.x() + armSize, centr.y() + bodySize / 2 + headSize.second);
}

void Human::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}


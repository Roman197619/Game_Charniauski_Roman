#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include "controller.h"
#include "human.h"
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <cmath>
#include <QGraphicsView>
#include <QPolygonF>

class GraphicsController :public QWidget
{
public:
   GraphicsController();

   QGraphicsView* getView() const;
   QGraphicsScene* getScene() const;


   void show(){
      view->show();
   }

   void drawMap(const QVector<Hexagon *> hexagonGrid);
   void redrawMap(Hexagon *);
   void drawUnits(const QVector<Human*>);
   void drawApples(QVector<Apple *> apples);
   void drawScores(int score1, int score2);

   void mouseMoveEvent(QMouseEvent *event, Controller *controller);

 public slots:
   void updateScores(int i, int j);


private:
   QGraphicsView* view;
   QGraphicsScene* scene;

   QGraphicsTextItem* text1;
   QGraphicsTextItem* text2;
};




#endif // GRAPHICSCONTROLLER_H

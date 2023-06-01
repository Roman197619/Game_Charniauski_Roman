#include "graphicscontroller.h"
#include "human.h"


GraphicsController::GraphicsController(): scene(new QGraphicsScene(this)), view(new QGraphicsView(this))
{

   text1 = new QGraphicsTextItem("Score 1: " + QString::number(0));
   text2 = new QGraphicsTextItem("Score 2: " + QString::number(0));
   text1->setZValue(10);
   text2->setZValue(10);
   text1->setPos(50, 50);
   text2->setPos(this->width() - 100, 50);
view->setScene(scene);
scene->addItem(text1);
scene->addItem(text2);
setMouseTracking(true);
}

QGraphicsView* GraphicsController::getView() const {
return view;
}

QGraphicsScene* GraphicsController::getScene() const{
return scene;
}


void GraphicsController::drawMap(const QVector<Hexagon*> hexagonGrid)
{
//    scene->clear();
    for (const auto& item : hexagonGrid) {
        scene->addItem(item->getPOlygon());
    }
}

void GraphicsController::redrawMap(Hexagon* item)
{
   scene->update(item->getPOlygon()->sceneBoundingRect());
}

void GraphicsController::drawUnits(const QVector<Human*> characters) {
   for (const auto charac : characters) {
      charac->addToScene(scene);
   }
}
void GraphicsController::drawApples(QVector<Apple*> apples) {
   for (auto item : apples) {
   scene->addItem(item);
   }
}

void GraphicsController::drawScores(int score1, int score2) {
    text1->setPlainText("Score 1: " + QString::number(score1));
    text2->setPlainText("Score 2: " + QString::number(score2));
   \
  text1->update();
  text2->update();
}

void GraphicsController::updateScores(int i, int j) {
   drawScores(i, j);
}

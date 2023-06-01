#include "controller.h"
#include <cmath>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QRandomGenerator>

Controller::Controller(QObject *parent) :
   QObject(parent)
{
   score1 = 0;
   score2 = 0;
}

const QVector<Hexagon*> Controller::getHexGrid() const
{
   return hexGrid;
}

void Controller::setHexColor(int i, QColor color)
{
}

QVector<Human*> Controller::getCharacters() const
{
    return characters;
}

void Controller::setCharacters(const QVector<Human *> &characters)
{
    this->characters = characters;
}

QVector<Apple*> Controller::getApples() const
{
    return apples;
}

void Controller::addApple(Apple* apple) {
   apples.push_back(apple);
}

Hexagon* Controller::getItemAt(QPointF point)
{
   for (Hexagon* hex : hexGrid)
   {
      if (hex->contains(point))
      {
         return hex;
      }
   }
   return nullptr;
}

void Controller::setApples(const QVector<Apple*>& apples)
{
    this->apples = apples;
}

void Controller::addCharacter(Human* character)
{
    characters.push_back(character);
}

void Controller::removeItem(int index)
{
    if (index >= 0 && index < apples.size()) {
        apples.remove(index);
    }
}

void Controller::slotDeleteApple(QGraphicsItem * item) {
   Apple* apple = dynamic_cast<Apple*> (item);
   apples.removeOne(apple);
   delete apple;
   emit score1Changed(score1++, score2);
}
void Controller::slotCreateApple() {

}

void Controller::removeCharacter(int index)
{
    if (index >= 0 && index < characters.size()) {
        characters.remove(index);
    }
}

void Controller::createAppleLayoout() {

   std::random_device rd;
   std::mt19937 mersenne(rd());

   int x = 0;
       for (int count = 0; count < 10; ++count)
       {
           x = mersenne() % hexGrid.size();
           if (!hexGrid[x]->IsFilled) {
           Apple* apple = new Apple();
           apple->setPos(hexGrid[x]->getCenter());
           apples.push_back(apple);
           }
       }

//   for (int i = 0; i < 10; i++ ) {
//      QRandomGenerator* generator = QRandomGenerator::global();
//   int x = generator->bounded(hexGrid.size()) ;
//   Apple* apple = new Apple();
//   if (!hexGrid[x]->IsFilled) {
//   apple->setPos(hexGrid[x]->getCenter());
//   apples.push_back(apple);
//   }
//   Apple* apple2 = new Apple();
//   if (!hexGrid[hexGrid.size() - x]->IsFilled) {
//   apple2->setPos(hexGrid[hexGrid.size() - x]->getCenter());
//   apples.push_back(apple2);
//   }
//   }
}

void Controller::createHexGrid(int width, int height, int hexSize) {
   qreal xOffset = hexSize * sqrt(3);
   qreal yOffset = hexSize * 3 / 2;
   for (int row = 0; row < height; ++row) {
       for (int col = 0; col < width; ++col) {
           QPointF hexCenter((col * xOffset) + ((row % 2) * xOffset / 2 ), row * yOffset );
           Hexagon* hexagon = new Hexagon(hexCenter);
           hexGrid.push_back(hexagon);
       }
   }
}

int Controller::getScore1() const {
    return score1;
}

void Controller::setScore1(int score) {
    if (score1 != score) {
        score1 = score;
        emit score1Changed(score1, score2);
    }
}

int Controller::getScore2() const {
    return score2;
}

void Controller::setScore2(int score) {
    if (score2 != score) {
        score2 = score;
        emit score2Changed(score1 , score2);
    }
}


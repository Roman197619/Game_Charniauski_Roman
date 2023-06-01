#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "apple.h"
#include "hexagon.h"
#include "human.h"
class Controller : public QObject
{
   Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);



   const QVector<Hexagon *> getHexGrid() const;

   void setHexColor(int i, QColor);
   Hexagon* getItemAt(QPointF point);
   QVector<Human *> getCharacters() const;
   void setCharacters(const QVector<Human*> &characters);

   QVector<Apple*> getApples() const;
   void setApples(const QVector<Apple*>& apples);
   void addApple(Apple*);

   void addCharacter(Human *character);
   void removeItem(int index);
//   void removeItem(Apple *item);
   void removeCharacter(int index);

   void createHexGrid(int width, int height, int hexSize);
   void createAppleLayoout();


   int getScore1() const;
   void setScore1(int score);
   int getScore2() const ;
   void setScore2(int score);

signals:
   void score1Changed(int newScore1, int score2);
   void score2Changed(int score1, int newScore2);

   void signalCheckItem(QGraphicsItem *);

public slots:
   void slotDeleteApple(QGraphicsItem * item);
   void slotCreateApple();



private:
   QVector<Hexagon*> hexGrid;
   QVector<Human*> characters;
   QVector<Apple*> apples;
   int score1;
   int score2;
};

#endif // CONTROLLER_H

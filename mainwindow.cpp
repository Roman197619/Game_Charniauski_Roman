#include "mainwindow.h"

#include <QDebug>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QPolygonF>
#include <QHBoxLayout>
#include <cmath>
#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "human.h"
#include "apple.h"
#include "pathFinder.h"

using Qt::NoItemFlags;

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent), controller(new Controller),
     graphicsController(new GraphicsController) {
   this->resize(1200, 1000);
   int hexSize = 70;
   int width = this->width() / (hexSize * sqrt(3));
   int height = this->height() / (hexSize * 3 / 2);
   controller->createHexGrid(width, height, hexSize);
   graphicsController->drawMap(controller->getHexGrid());

   controller->createAppleLayoout();
   graphicsController->drawApples(controller->getApples());


   graphicsController->getView()->viewport()->installEventFilter(this);

   graphicsController->drawScores(controller->getScore1(), controller->getScore2());
   setMouseTracking(true);

   gameTimer = new QTimer();
   connect(gameTimer, &QTimer::timeout, this, &MainWindow::slotGameTimer);
   gameTimer->start(1000 / 100);

 human = new Human(this);
 human->setCentr(controller->getHexGrid()[0]->getCenter());
 human->addToScene(graphicsController->getScene());
 controller->addCharacter(human);

connect(controller, &Controller::score1Changed, graphicsController, &GraphicsController::updateScores);
connect(controller, &Controller::score2Changed, graphicsController, &GraphicsController::updateScores);
connect(controller, &Controller::signalCheckItem, controller, &Controller::slotDeleteApple);




   setCentralWidget(graphicsController->getView());
   setFocus();
   centralWidget()->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotGameTimer() {
   QList<QGraphicsItem *> foundItems = graphicsController->getScene()->items(controller->getCharacters()[0]->getCenter());

   for (auto item : foundItems) {
      if (item == controller->getCharacters()[0])
          continue;
      if (dynamic_cast<Apple*> (item))
      emit controller->signalCheckItem(item);
   }
   graphicsController->drawScores(controller->getScore1(), controller->getScore2());
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
   QPointF pos = graphicsController->getView()->mapToScene(event->pos());
   for (int i = 0; i < controller->getHexGrid().size(); i++) {
      if (controller->getHexGrid()[i]->contains(pos)) {
         controller->setHexColor(i, Qt::black);
          graphicsController->redrawMap(controller->getHexGrid()[i]);
          break;
       }
   }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        rightMouseClick(event);
    }
    if (event->button() == Qt::LeftButton) {
        // Запустить таймер для отслеживания продолжительности удержания левой кнопки мыши
        // 100 мс - интервал таймера
    }
}

void MainWindow::rightMouseClick(QMouseEvent *event)
{
//   QPointF pos = graphicsController->getView()->mapToScene(event->pos());

//   for (int i = 0; i < controller->getHexGrid().size(); i++) {
//      if (controller->getHexGrid()[i]->contains(pos)) {
//         controller->setHexColor(i, Qt::black);
//          graphicsController->redrawMap(controller->getHexGrid()[i]);
//          break;
//       }
//   }
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Остановить таймер при отпускании левой кнопки мыши
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
    {
   if(event == nullptr)
      return QWidget::eventFilter(obj, event);

//        {
//            if (event->type() == QEvent::MouseMove)
//            {
//                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
//                MainWindow::mouseMoveEvent(mouseEvent);
//            }
//            else if (event->type() == QEvent::MouseButtonPress)
//            {
//                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
//                if (mouseEvent->button() == Qt::LeftButton)
//                {

//                }
//                else if (mouseEvent->button() == Qt::RightButton)
//                {
//                   MainWindow::rightMouseClick(mouseEvent);
//                   if (human != nullptr) {
//                      std::vector<int> indexes = FindPath(controller->getHexGrid(), 140, 5 ,10);
//                      QPainterPath* path = new QPainterPath();
//                      path->moveTo(controller->getHexGrid()[indexes[0]]->getCenter());
//                      for (auto index : indexes) {
//                                    path->lineTo(controller->getHexGrid()[index]->getCenter());
//                      }
//                      human->moveCenterAlongPath(*path);

//                               qDebug() << "Aaaaaaaaaaa";
//                         graphicsController->getScene()->update(human->boundingRect());
//                         }
//                }
//            }

            if (event->type() == QEvent::MouseMove)
            {
               QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                  QPointF pos = graphicsController->getView()->mapToScene(mouseEvent->pos());
               QGraphicsItem *item = controller->getItemAt(pos);
               if (item && item->type() == QGraphicsPolygonItem::Type)
               {
                  Hexagon *hex = static_cast<Hexagon*>(item);
                  QGraphicsSceneHoverEvent hoverEvent(QEvent::GraphicsSceneHoverMove);
                  hoverEvent.setScenePos(pos);
                  hex->IsFilled = true;
                  hex->hoverEnterEvent(&hoverEvent);
                  //qDebug() << "mmglm";
                  for (Hexagon *hex : controller->getHexGrid())
                        {
                           if (hex->IsFilled && !hex->contains(pos))
                           {
                              hex->IsFilled = false;
                              QGraphicsSceneHoverEvent hoverEventLeave(QEvent::GraphicsSceneHoverMove);
                              hoverEventLeave.setScenePos(pos);
                              hex->hoverLeaveEvent(&hoverEvent);
                              break;
                           }
                  }
               }
            }

            if (event->type() == QEvent::MouseButtonPress)
                        {
                            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                            QPointF pos = graphicsController->getView()->mapToScene(mouseEvent->pos());
               if (mouseEvent->button() == Qt::RightButton && !(controller->getCharacters()[0]->getAnimation().state() == QAbstractAnimation::Running)) {
                  {
                     std::vector<int> indexes = FindPath(controller->getHexGrid(), 140,
                                                         controller->getHexGrid().indexOf(controller->getItemAt(controller->getCharacters()[0]->getCenter())),
                                                         controller->getHexGrid().indexOf(controller->getItemAt(pos)));
                     QPainterPath* path = new QPainterPath();
                     path->moveTo(controller->getHexGrid()[indexes[0]]->getCenter());
                     for (auto index : indexes) {
                                   path->lineTo(controller->getHexGrid()[index]->getCenter());
                     }
                     human->moveCenterAlongPath(*path);

                       //       qDebug() << "Aaaaaaaaaaa";
                        graphicsController->getScene()->update(human->boundingRect());
                        }
               }
            }


        return QWidget::eventFilter(obj, event);
};






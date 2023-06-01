//#include "mainwindow.h"
//#include "graphicscontroller.h".h"
//#include <QApplication>

//int main(int argc, char *argv[])
//{
//   QApplication a(argc, argv);
//   HexagonGrid grid;
//   grid.resize(500, 500);
//   grid.show();
//   return a.exec();
//}


#include "human.h"
#include "mainwindow.h"
#include "qgraphicsscene.h"
#include "qgraphicsview.h"

#include <QApplication>
#include<QDesktopWidget>

int main(int argc, char *argv[])
{
//   QApplication app(argc, argv);

//   QGraphicsScene scene;
//   scene.setSceneRect(0, 0, 400, 300);
//   scene.setBackgroundBrush(QColor(0, 0, 255));

//   QGraphicsView view(&scene);

//   Human *human = new Human;
//   scene.addItem(human);

//   view.show();

//   return app.exec();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
//       QApplication a(argc, argv);
//       Widget w;
//       w.resize(a.desktop()->size());
//       w.show();


}

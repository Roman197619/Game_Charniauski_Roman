#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "controller.h"
#include "graphicscontroller.h"
#include "human.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
   void mouseMoveEvent(QMouseEvent *event) override;
   void mousePressEvent(QMouseEvent *event) override;
   void mouseReleaseEvent(QMouseEvent *event) override;
   void rightMouseClick(QMouseEvent *event);

 public slots:
   void slotGameTimer();

private:
   bool eventFilter(QObject *object, QEvent *event) override;
    void createHexagonalGrid(int width, int height, int hexSize);
Human* human;
Controller *controller;
GraphicsController *graphicsController;
 QTimer* gameTimer;
};

#endif // MAINWINDOW_H

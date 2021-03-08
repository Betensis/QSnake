#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(cellsSize.width() * fieldSize.width(), cellsSize.height() * fieldSize.height());
    timer = new QTimer();
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    field.draw(painter);
}

void MainWindow::keyPressEvent(QKeyEvent *kb)
{
    switch (kb->key()) {
    case Qt::Key_Up:
        field.setSnakeMoveDirection(0);
        break;
    case Qt::Key_Down:
        field.setSnakeMoveDirection(1);
        break;
    case Qt::Key_Right:
        field.setSnakeMoveDirection(2);
        break;
    case Qt::Key_Left:
        field.setSnakeMoveDirection(3);
        break;
    }
}

void MainWindow::updateGame()
{
    repaint();
}


#ifndef SNAKE_H
#define SNAKE_H

#include <QVector>
#include <QPainter>
#include <queue>
#include "cell.h"


class Snake
{
public:
    enum allMoveDirections : int {
        UP,
        DOWN,
        RIGHT,
        LEFT,
    };

    Snake(QSize cellsSize, int length = 3, QColor color = QColor(135, 235, 0), QSize fieldSize = QSize(25, 25));
    void draw(QPainter &painter);
    void move();
    void eatFood(FoodCell food);

    void setMoveDirection(const allMoveDirections &value);
    void setMoveDirection(int value);

    bool isAlive() const;
    QPoint getHeadCoord();

    QVector<Cell> getArrCells() const;
    Cell getHeadCell();

    void setDeadCondition();
private:
    bool isSelfIntersection();
    QSize fieldSize;
    bool alive = true;
    QSize cellsSize;
    int length = 3;
    allMoveDirections moveDirection = allMoveDirections::RIGHT;
    QVector<Cell> arrCells;
};

#endif // SNAKE_H

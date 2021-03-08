#ifndef FIELD_H
#define FIELD_H

#include "cell.h"
#include "snake.h"
#include <QPainter>
#include <QDebug>


class Field
{
public:
    Field(QSize fieldSize, QSize cellsSize, QColor snakeColor);
    void draw(QPainter &painter);
    void setSnakeMoveDirection(int moveDirecion);
    void relocateMushroom();
private:
    bool isCellInMushroom(Cell cell);
    void drawMushroom(QPainter &painter);
    int mushroomDiameter;
    QPoint mushroomCoord;
    QPoint getRandCellCoord();
    QSize fieldSize;
    Snake snake;
    QVector<QVector<Cell>> arrCells;
    FoodCell food = FoodCell(QSize(0,0), QPoint(0,0), QColor(0,0,0));
    QSize getCellSize();
};

#endif // FIELD_H

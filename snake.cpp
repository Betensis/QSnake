#include "snake.h"

#include <QDebug>


Snake::Snake(QSize cellsSize, int length, QColor color,QSize fieldSize)
    : fieldSize(fieldSize), cellsSize(cellsSize), length(length)
{
    for (int i = length - 1; i >= 0; i--)
    {
        arrCells.push_back(Cell(cellsSize, QPoint(0, i * cellsSize.height()), color));
    }
    this->setMoveDirection(allMoveDirections::DOWN);
}

void Snake::draw(QPainter &painter)
{
    for (int i = 0; i < arrCells.length(); i++){
        arrCells[i].draw(painter);
    }
    // Дальше рисуется голова
    QPoint headCellCoord = arrCells[0].getCoord();
    auto halfCellWidth = cellsSize.width() * 0.5;
    auto halfCellHidth = cellsSize.height() * 0.5;
    painter.setBrush(QColor(0,0,0));
    QSize quarterCellSize(halfCellWidth, halfCellHidth);
    switch (moveDirection) {
    case UP:
        painter.drawEllipse(QRect(headCellCoord, quarterCellSize));
        painter.drawEllipse(QRect(headCellCoord + QPoint(halfCellWidth, 0), quarterCellSize));
        break;
    case DOWN:
        painter.drawEllipse(QRect(headCellCoord + QPoint(0, halfCellHidth), quarterCellSize));
        painter.drawEllipse(QRect(headCellCoord + QPoint(halfCellWidth, halfCellHidth), quarterCellSize));
        break;
    case RIGHT:
        painter.drawEllipse(QRect(headCellCoord + QPoint(halfCellWidth, 0), quarterCellSize));
        painter.drawEllipse(QRect(headCellCoord + QPoint(halfCellWidth, halfCellHidth), quarterCellSize));
        break;
    case LEFT:
        painter.drawEllipse(QRect(headCellCoord, quarterCellSize));
        painter.drawEllipse(QRect(headCellCoord + QPoint(0, halfCellHidth), quarterCellSize));
        break;
    }
}

void Snake::move()
{
    if (!alive)
        return;
    QPoint headCellCoord = arrCells[0].getCoord();
    auto lastCell = arrCells.takeLast();

    switch (moveDirection) {
    case UP:
        if (headCellCoord.y() != 0){
            lastCell.resetCoordAndColor(headCellCoord - QPoint(0, cellsSize.height()));
        }
        else {
            setDeadCondition();
        }
        break;
    case DOWN:
        if (headCellCoord.y()!= cellsSize.height()*(fieldSize.height() - 1)){
            lastCell.resetCoordAndColor(headCellCoord + QPoint(0, cellsSize.height()));
        }
        else {
            setDeadCondition();
        }
        break;
    case RIGHT:
        if (headCellCoord.x() != (fieldSize.width() - 1)*cellsSize.width()){
            lastCell.resetCoordAndColor(headCellCoord + QPoint(cellsSize.width(), 0));
        }
        else {
            setDeadCondition();
        }
        break;
    case LEFT:
        if (headCellCoord.x() != 0){
            lastCell.resetCoordAndColor(headCellCoord - QPoint(cellsSize.width(), 0));
        }
        else {
            setDeadCondition();
        }
        break;
    }
    if (alive)
        arrCells.insert(0, lastCell);
    else
        arrCells.push_back(lastCell);
    if (isSelfIntersection())
        setDeadCondition();
}

void Snake::eatFood(FoodCell food)
{
    if (food.isAsid())
        setDeadCondition();
    arrCells.push_back(Cell(arrCells.last()));
    length += 1;
}


void Snake::setMoveDirection(const allMoveDirections &value)
{
    if (!alive)
        return;
    switch (value) {
    case UP:
        if(this->moveDirection == allMoveDirections::DOWN)
            return;
        break;
    case DOWN:
        if (this->moveDirection == allMoveDirections::UP)
            return;
        break;
    case RIGHT:
        if (this->moveDirection == allMoveDirections::LEFT)
            return;
        break;
    case LEFT:
        if (this->moveDirection == allMoveDirections::RIGHT)
            return;
        break;
    }
    moveDirection = value;
}

void Snake::setMoveDirection(int value)
{
    setMoveDirection(static_cast<allMoveDirections>(value));
}

bool Snake::isAlive() const
{
    return alive;
}

QPoint Snake::getHeadCoord()
{
    return arrCells[0].getCoord();
}

QVector<Cell> Snake::getArrCells() const
{
    return arrCells;
}

Cell Snake::getHeadCell()
{
    return arrCells[0];
}

void Snake::setDeadCondition()
{
    this->alive = false;
    for (int i = 0; i < arrCells.length(); i++)
        arrCells[i].setColor(QColor(167, 158, 98, 90));
}

bool Snake::isSelfIntersection()
{
    for (int i = 1; i < arrCells.length(); i++){
        if (arrCells[0].getCoord() == arrCells[i].getCoord())
            return true;
    }
    return false;
}

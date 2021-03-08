#include "cell.h"

Cell::Cell(QSize size,QPoint coord, QColor color)
    : coord(coord), size(size), color(color)
{
}

Cell::Cell(const Cell &cell)
    : coord(cell.coord), size(cell.size), color(cell.color)
{
}

void Cell::draw(QPainter &painter)
{
    QRect rect = QRect(coord, QPoint(coord.x() + size.width(), coord.y() + size.height()));
    painter.setBrush(QBrush(color));
    painter.drawRect(rect);
}

QPoint Cell::getCoord() const
{
    return coord;
}

void Cell::resetCoordAndColor(const QPoint &value)
{
    coord = value;
    this->color = QColor(64, 239, 72);
}

QColor Cell::getColor() const
{
    return color;
}

void Cell::setColor(const QColor &value)
{
    color = value;
}

QSize Cell::getSize() const
{
    return size;
}


FoodCell::FoodCell(QSize size, QPoint coord, QColor color)
    :Cell(size, coord, color)
{
}

void FoodCell::draw(QPainter &painter)
{

    if (isAsid())
        setColor(QColor(236, 0, 0));
    this->::Cell::draw(painter);
}

void FoodCell::resetCoordAndColor(const QPoint &value)
{
    this->coord = value;
    this->color = QColor(104, 239, 138);
}

bool FoodCell::isAsid() const
{
    return asid;
}

void FoodCell::setIsAsid(bool value)
{
    asid = value;
}

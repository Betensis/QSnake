#ifndef CELL_H
#define CELL_H

#include <QPainter>

class Cell
{
public:
    Cell(QSize size,QPoint coord, QColor color = QColor(147, 147, 147));
    Cell(const Cell &cell);
    virtual void draw(QPainter &painter);
    QPoint getCoord() const;
    virtual void resetCoordAndColor(const QPoint &value);
    QColor getColor() const;
    void setColor(const QColor &value);
    QSize getSize() const;

protected:
    QPoint coord;
    QSize size;
    QColor color;
};

class FoodCell : public Cell
{
public:
    FoodCell(QSize size,QPoint coord, QColor color = QColor(104, 239, 138));
    virtual void draw(QPainter &painter);
    virtual void resetCoordAndColor(const QPoint &value);
    bool isAsid() const;
    void setIsAsid(bool value);

private:
    bool asid = false;
};

#endif // CELL_H

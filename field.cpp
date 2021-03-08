#include "field.h"

Field::Field(QSize fieldSize, QSize cellsSize, QColor snakeColor)
    :fieldSize(fieldSize), snake(Snake(cellsSize, 3, snakeColor))
{

    for (int i = 0; i < fieldSize.height(); i++)
    {
        arrCells.push_back(QVector<Cell>());
        for (int j = 0; j < fieldSize.width(); j++)
        {
            arrCells[i].push_back(Cell(cellsSize, QPoint(j * cellsSize.width(), i * cellsSize.height())));
        }
    }
    food = FoodCell(cellsSize, getRandCellCoord());
    mushroomDiameter = arrCells[0][0].getSize().width()*2;
    std::srand(std::time(nullptr));
    relocateMushroom();
    food.setIsAsid(false);
}

void Field::draw(QPainter &painter)
{
    for (int i = 0; i < fieldSize.height(); i++)
    {
        for (int j = 0; j < fieldSize.width(); j++)
        {
            arrCells[i][j].draw(painter);
        }
    }
    if (isCellInMushroom(food))
        food.setIsAsid(true);
    if (isCellInMushroom(snake.getHeadCell()))
        snake.setDeadCondition();
    drawMushroom(painter);
    snake.move();
    snake.draw(painter);
    if (snake.getHeadCoord() == food.getCoord())
    {
        food.resetCoordAndColor(getRandCellCoord());
        snake.eatFood(food);
    }
    food.draw(painter);
    if (mushroomDiameter > arrCells[0][0].getSize().width() * 6){
        relocateMushroom();
        mushroomDiameter = arrCells[0][0].getSize().width() * 1.25;
    }
    else {
        mushroomDiameter += arrCells[0][0].getSize().width() * 0.25;
    }
    // рисуем мухомор
}

void Field::setSnakeMoveDirection(int moveDirection)
{
    snake.setMoveDirection(moveDirection);
}

void Field::relocateMushroom()
{
    while (1){
        auto randCoord = getRandCellCoord();
        mushroomCoord = randCoord;
        if (!isCellInMushroom(snake.getHeadCell())){
            return;
        }
    }
}

bool Field::isCellInMushroom(Cell cell)
{
    if ((mushroomDiameter * 0.5) > std::sqrt(pow(cell.getCoord().x() - mushroomCoord.x(), 2) +
                                     pow(cell.getCoord().y() - mushroomCoord.y(), 2)))
        return true;
    if ((mushroomDiameter * 0.5) > std::sqrt(pow(cell.getCoord().x() + getCellSize().width() - mushroomCoord.x(), 2) +
                                     pow(cell.getCoord().y() - mushroomCoord.y(), 2)))
        return true;
    if ((mushroomDiameter * 0.5) > std::sqrt(pow(cell.getCoord().x() - mushroomCoord.x(), 2) +
                                     pow(cell.getCoord().y() + getCellSize().height() - mushroomCoord.y(), 2)))
        return true;
    if ((mushroomDiameter * 0.5) > std::sqrt(pow(cell.getCoord().x() + getCellSize().width() - mushroomCoord.x(), 2) +
                                     pow(cell.getCoord().y() + getCellSize().height() - mushroomCoord.y(), 2)))
        return true;
    return false;
}

void Field::drawMushroom(QPainter &painter)
{
    painter.setBrush(QColor(192, 20, 20, 50));
    painter.drawEllipse(mushroomCoord.x() - mushroomDiameter * 0.5, mushroomCoord.y() - mushroomDiameter * 0.5, mushroomDiameter, mushroomDiameter);
}

QPoint Field::getRandCellCoord()
{

    return QPoint((std::rand() % (fieldSize.width())) * arrCells[0][0].getSize().width(),
            (std::rand() % (fieldSize.height()) * arrCells[0][0].getSize().height()));
}

QSize Field::getCellSize()
{
    return arrCells[0][0].getSize();
}


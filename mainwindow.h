#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include "field.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* kb);
private:
    QSize fieldSize = QSize(25, 25);
    QSize cellsSize = QSize(24, 24);
    QColor snakeColor = QColor(135, 235, 145);

    Field field = Field(fieldSize, cellsSize, snakeColor);
    Ui::MainWindow *ui;

    QTimer *timer;
private slots:
    void updateGame();
};
#endif // MAINWINDOW_H

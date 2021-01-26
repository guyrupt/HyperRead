#ifndef MLABEL_H
#define MLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>

class mlabel : public QLabel
{
    Q_OBJECT
public:
    explicit mlabel(QWidget *parent = nullptr);

    int x,y;

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event); //--按左鍵

    int img_x,img_y;
signals:
    void mouse_pos();
    void mouse_press();

public slots:
};

#endif // MLABEL_H

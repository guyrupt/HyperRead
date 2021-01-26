#include "mlabel.h"

mlabel::mlabel(QWidget *parent) : QLabel(parent)
{

}

void mlabel::mouseMoveEvent(QMouseEvent *event)
{
    this->x = event->x();
    this->y = event->y();
    emit mouse_pos();
}

void mlabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton &&
            event->modifiers() == Qt::ControlModifier){
        this->img_x = event->x();
        this->img_y = event->y();
        emit mouse_press();
    }
}

#include "qprossbarlabel.h"



Qprossbarlabel::Qprossbarlabel(QWidget *parent) : QWidget(parent)
{
    dval = 0;
    dstr="准备";

}

void Qprossbarlabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    initCoordinateSystem(painter);

    painter.setPen(Qt::black);
    painter.setBrush(QColor("#1E90FF"));

    painter.drawRect(0,0,dval*width(),height());

    QFont font("Arial");
    font.setBold(true);
    font.setPixelSize(12);
    painter.setFont(font);
    painter.drawText(5,height()-10,dstr);
}

void Qprossbarlabel::initCoordinateSystem(QPainter &painter)
{
    // inicjalizacja paintera
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.translate(width() / 2, height() / 2);
    //painter.translate( width()/2.0,0.0);
    //painter.scale( width()/ 100.0, width()/ 100.0);
}

void Qprossbarlabel::setdval(double val)
{
    dval = val;
    update();
}

void Qprossbarlabel::setText(QString str)
{
    dstr = str;
    update();
}

QString Qprossbarlabel::getdstr()
{
    return dstr;
}

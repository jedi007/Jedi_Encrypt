#ifndef QPROSSBARLABEL_H
#define QPROSSBARLABEL_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QDebug>

class Qprossbarlabel : public QWidget
{
    Q_OBJECT
public:
    explicit Qprossbarlabel(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);

    void initCoordinateSystem(QPainter & painter);
    void setdval(double val);
    void setText(QString str);
    QString getdstr();

signals:

public slots:

private:
    double dval;
    QString dstr;
};

#endif // QPROSSBARLABEL_H

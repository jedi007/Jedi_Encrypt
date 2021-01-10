#include "statusview.h"

#include <QHeaderView>
#include <QResizeEvent>
#include <QDebug>

StatusView::StatusView(QWidget *parent):QTableView(parent)
{
    setColumnWidth(1,100);

    setSelectionMode(QTableView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
}

void StatusView::resizeEvent(QResizeEvent *event)
{
    qDebug()<<"resizeEvent "<<event->size()<<endl;



    horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);

    //setColumnWidth(1,100);

    QTableView::resizeEvent(event);
}

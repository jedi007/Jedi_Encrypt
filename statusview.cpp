#include "statusview.h"

#include <QHeaderView>
#include <QResizeEvent>
#include <QDebug>

StatusView::StatusView(QWidget *parent):QTableView(parent)
{

}

void StatusView::resizeEvent(QResizeEvent *event)
{
    qDebug()<<"resizeEvent "<<event->size()<<endl;



    horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);

    setColumnWidth(1,100);
}

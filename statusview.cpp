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
    horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);

    QTableView::resizeEvent(event);
}

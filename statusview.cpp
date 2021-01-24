#include "statusview.h"

#include <QHeaderView>
#include <QResizeEvent>
#include <QDebug>

#include "encryptlistmodel.h"

StatusView::StatusView(QWidget *parent):QTableView(parent)
{
    setColumnWidth(1,100);
    setColumnWidth(2,200);
    setSelectionMode(QTableView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行

    timerID = startTimer(100);
}

void StatusView::resizeEvent(QResizeEvent *event)
{
    horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);

    QTableView::resizeEvent(event);
}

void StatusView::timerEvent(QTimerEvent *event)
{
    QTableView::timerEvent(event);
    EncryptListModel* listmodel = dynamic_cast<EncryptListModel*>(model());
    if(listmodel)
        listmodel->refresh();
}

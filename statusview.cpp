#include "statusview.h"

#include <QHeaderView>
#include <QResizeEvent>
#include <QDebug>

#include "encryptlistmodel.h"
#include "mainwindow.h"

StatusView::StatusView(QWidget *parent):QTableView(parent)
{
    setSelectionMode(QTableView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行

    timerID = startTimer(100);
}

void StatusView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
    setColumnWidth(1,100);
    setColumnWidth(2,300);
    horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
}

void StatusView::timerEvent(QTimerEvent *event)
{
    QTableView::timerEvent(event);

    EncryptListModel* listmodel = dynamic_cast<EncryptListModel*>(model());
    if(listmodel->status.size()<1) return;

    if(listmodel)
        listmodel->refresh();
    foreach (const EncryptState& state, listmodel->status) {
        if( !state.over )
            return;
    }
    emit changeEnabled(true);
}

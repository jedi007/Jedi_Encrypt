#ifndef STATUSVIEW_H
#define STATUSVIEW_H

#include <QTableView>

class StatusView : public QTableView
{
    Q_OBJECT
public:
    StatusView(QWidget *parent = nullptr);

    virtual void resizeEvent(QResizeEvent *event);
};

#endif // STATUSVIEW_H

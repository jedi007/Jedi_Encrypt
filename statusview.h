#ifndef STATUSVIEW_H
#define STATUSVIEW_H

#include <QTableView>

class StatusView : public QTableView
{
    Q_OBJECT
public:
    StatusView(QWidget *parent = nullptr);

    virtual void resizeEvent(QResizeEvent *event) override;

    int timerID;
    virtual void timerEvent(QTimerEvent *event) override;

signals:
    void changeEnabled(bool b);
};

#endif // STATUSVIEW_H

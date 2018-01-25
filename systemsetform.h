#ifndef SYSTEMSETFORM_H
#define SYSTEMSETFORM_H

#include <QWidget>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#include "global.h"

namespace Ui {
class SystemSetForm;
}

class SystemSetForm : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSetForm(QWidget *parent = 0);
    ~SystemSetForm();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::SystemSetForm *ui;
};

#endif // SYSTEMSETFORM_H

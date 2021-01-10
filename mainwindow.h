#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "myfilesystemmodel.h"
#include "encryptlistmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_import_dir_clicked();

    void on_pushButton_encrypt_dir_clicked();

    void on_pushButton_dencrypt_dir_clicked();

    void on_pushButton_import_file_clicked();

    void on_pushButton_encrypt_clicked();

    void on_pushButton_decrypt_clicked();

private:
    Ui::MainWindow *ui;

    MyFileSystemModel* myModel = nullptr;
    EncryptListModel* statusModel = nullptr;

    void initMymolde();
};
#endif // MAINWINDOW_H

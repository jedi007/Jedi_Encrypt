/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionshezhi;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *BTimport;
    QPushButton *BTencypt;
    QPushButton *BTdecypt;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *BTpause;
    QPushButton *BTcontinue;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1058, 568);
        actionshezhi = new QAction(MainWindow);
        actionshezhi->setObjectName(QStringLiteral("actionshezhi"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(0, 0));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        BTimport = new QPushButton(centralWidget);
        BTimport->setObjectName(QStringLiteral("BTimport"));

        horizontalLayout->addWidget(BTimport);

        BTencypt = new QPushButton(centralWidget);
        BTencypt->setObjectName(QStringLiteral("BTencypt"));

        horizontalLayout->addWidget(BTencypt);

        BTdecypt = new QPushButton(centralWidget);
        BTdecypt->setObjectName(QStringLiteral("BTdecypt"));

        horizontalLayout->addWidget(BTdecypt);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        BTpause = new QPushButton(centralWidget);
        BTpause->setObjectName(QStringLiteral("BTpause"));

        horizontalLayout->addWidget(BTpause);

        BTcontinue = new QPushButton(centralWidget);
        BTcontinue->setObjectName(QStringLiteral("BTcontinue"));

        horizontalLayout->addWidget(BTcontinue);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1058, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionshezhi);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Jedi\345\212\240\345\257\206\347\263\273\347\265\261", Q_NULLPTR));
        actionshezhi->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\346\272\220\346\226\207\344\273\266", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\345\244\247\345\260\217", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\345\212\240\345\257\206\345\274\272\345\272\246", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\347\256\227\346\263\225", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272\350\267\257\345\276\204", Q_NULLPTR));
        BTimport->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\346\226\207\344\273\266", Q_NULLPTR));
        BTencypt->setText(QApplication::translate("MainWindow", "\345\212\240\345\257\206", Q_NULLPTR));
        BTdecypt->setText(QApplication::translate("MainWindow", "\350\247\243\345\257\206", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("MainWindow", "123456", Q_NULLPTR));
        BTpause->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", Q_NULLPTR));
        BTcontinue->setText(QApplication::translate("MainWindow", "\347\273\247\347\273\255", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\347\263\273\347\273\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

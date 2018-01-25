/********************************************************************************
** Form generated from reading UI file 'systemsetform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSETFORM_H
#define UI_SYSTEMSETFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemSetForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLabel *outfile_label;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *SystemSetForm)
    {
        if (SystemSetForm->objectName().isEmpty())
            SystemSetForm->setObjectName(QStringLiteral("SystemSetForm"));
        SystemSetForm->resize(285, 284);
        verticalLayout_2 = new QVBoxLayout(SystemSetForm);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(SystemSetForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout_3->addWidget(checkBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(label_4);

        outfile_label = new QLabel(groupBox);
        outfile_label->setObjectName(QStringLiteral("outfile_label"));

        horizontalLayout_4->addWidget(outfile_label);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(SystemSetForm);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 100));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalSlider = new QSlider(groupBox_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimumSize(QSize(0, 20));
        horizontalSlider->setMaximum(2);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 200));

        horizontalLayout->addWidget(label, 0, Qt::AlignTop);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(16777215, 200));

        horizontalLayout->addWidget(label_3, 0, Qt::AlignHCenter|Qt::AlignTop);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 200));

        horizontalLayout->addWidget(label_2, 0, Qt::AlignRight|Qt::AlignTop);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(SystemSetForm);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        comboBox = new QComboBox(groupBox_3);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_5->addWidget(comboBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_2->addWidget(groupBox_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(SystemSetForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(SystemSetForm);

        QMetaObject::connectSlotsByName(SystemSetForm);
    } // setupUi

    void retranslateUi(QWidget *SystemSetForm)
    {
        SystemSetForm->setWindowTitle(QApplication::translate("SystemSetForm", "\347\263\273\347\273\237\350\256\276\347\275\256", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SystemSetForm", "\351\273\230\350\256\244\350\276\223\345\207\272\350\267\257\345\276\204\350\256\276\347\275\256", Q_NULLPTR));
        checkBox->setText(QApplication::translate("SystemSetForm", "\344\275\277\347\224\250\346\272\220\346\226\207\344\273\266\350\267\257\345\276\204", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SystemSetForm", "\350\256\276\347\275\256\350\276\223\345\207\272\350\267\257\345\276\204", Q_NULLPTR));
        label_4->setText(QApplication::translate("SystemSetForm", "\345\275\223\345\211\215\350\276\223\345\207\272\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        outfile_label->setText(QString());
        groupBox_2->setTitle(QApplication::translate("SystemSetForm", "\345\212\240\345\257\206\347\272\247\345\210\253", Q_NULLPTR));
        label->setText(QApplication::translate("SystemSetForm", "\345\210\235\347\272\247", Q_NULLPTR));
        label_3->setText(QApplication::translate("SystemSetForm", "\344\270\255\347\272\247", Q_NULLPTR));
        label_2->setText(QApplication::translate("SystemSetForm", "\351\253\230\347\272\247", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("SystemSetForm", "\346\234\200\345\244\247\347\272\277\347\250\213\346\225\260", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SystemSetForm", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SystemSetForm: public Ui_SystemSetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSETFORM_H

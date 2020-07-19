/********************************************************************************
** Form generated from reading UI file 'viewCalculate.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWCALCULATE_H
#define UI_VIEWCALCULATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewCalculate
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBox;
    QPushButton *btn_Cal;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *viewCalculate)
    {
        if (viewCalculate->objectName().isEmpty())
            viewCalculate->setObjectName(QString::fromUtf8("viewCalculate"));
        viewCalculate->resize(525, 409);
        centralwidget = new QWidget(viewCalculate);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 505, 142));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout->addWidget(spinBox);

        btn_Cal = new QPushButton(centralwidget);
        btn_Cal->setObjectName(QString::fromUtf8("btn_Cal"));

        horizontalLayout->addWidget(btn_Cal);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 5);

        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(true);

        verticalLayout->addWidget(textEdit);

        verticalLayout->setStretch(0, 4);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 2);
        viewCalculate->setCentralWidget(centralwidget);
        menubar = new QMenuBar(viewCalculate);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 525, 22));
        viewCalculate->setMenuBar(menubar);
        statusbar = new QStatusBar(viewCalculate);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        viewCalculate->setStatusBar(statusbar);

        retranslateUi(viewCalculate);

        QMetaObject::connectSlotsByName(viewCalculate);
    } // setupUi

    void retranslateUi(QMainWindow *viewCalculate)
    {
        viewCalculate->setWindowTitle(QCoreApplication::translate("viewCalculate", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("viewCalculate", "\347\262\276\345\272\246(\347\262\276\347\241\256\345\210\260\345\260\217\346\225\260\347\202\271\345\220\216n\344\275\215)", nullptr));
        btn_Cal->setText(QCoreApplication::translate("viewCalculate", "\347\241\256\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("viewCalculate", "\347\255\224\346\241\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewCalculate: public Ui_viewCalculate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWCALCULATE_H

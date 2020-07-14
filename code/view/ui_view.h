/********************************************************************************
** Form generated from reading UI file 'view.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_View
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayoutBody;
    QLabel *latexLabel;
    QLabel *imgLabel;
    QGridLayout *gridLayout;
    QPlainTextEdit *imgInfo;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_4;
    QRadioButton *mathpixButton;
    QRadioButton *baidu_Button;
    QPushButton *loadButton;
    QPushButton *downloadButton;
    QPushButton *resetButton;
    QLabel *delimiter;
    QLabel *label;
    QPushButton *editButton;
    QPushButton *calculateButton;
    QLabel *label_5;
    QMenuBar *titleMenuBar;

    void setupUi(QMainWindow *View)
    {
        if (View->objectName().isEmpty())
            View->setObjectName(QString::fromUtf8("View"));
        View->resize(960, 626);
        centralwidget = new QWidget(View);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(-1, -1, 961, 591));
        gridLayoutBody = new QGridLayout(gridLayoutWidget);
        gridLayoutBody->setObjectName(QString::fromUtf8("gridLayoutBody"));
        gridLayoutBody->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayoutBody->setVerticalSpacing(0);
        gridLayoutBody->setContentsMargins(0, 0, 0, 0);
        latexLabel = new QLabel(gridLayoutWidget);
        latexLabel->setObjectName(QString::fromUtf8("latexLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(latexLabel->sizePolicy().hasHeightForWidth());
        latexLabel->setSizePolicy(sizePolicy);

        gridLayoutBody->addWidget(latexLabel, 1, 0, 1, 1);

        imgLabel = new QLabel(gridLayoutWidget);
        imgLabel->setObjectName(QString::fromUtf8("imgLabel"));
        sizePolicy.setHeightForWidth(imgLabel->sizePolicy().hasHeightForWidth());
        imgLabel->setSizePolicy(sizePolicy);

        gridLayoutBody->addWidget(imgLabel, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        imgInfo = new QPlainTextEdit(gridLayoutWidget);
        imgInfo->setObjectName(QString::fromUtf8("imgInfo"));
        imgInfo->setReadOnly(true);

        gridLayout->addWidget(imgInfo, 7, 1, 1, 3);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 4, 1, 1, 3);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 10, 1, 1, 3);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 4, 11, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 0, 1, 1, 3);

        mathpixButton = new QRadioButton(gridLayoutWidget);
        mathpixButton->setObjectName(QString::fromUtf8("mathpixButton"));
        mathpixButton->setChecked(true);

        gridLayout->addWidget(mathpixButton, 5, 3, 1, 1);

        baidu_Button = new QRadioButton(gridLayoutWidget);
        baidu_Button->setObjectName(QString::fromUtf8("baidu_Button"));
        baidu_Button->setLayoutDirection(Qt::LeftToRight);
        baidu_Button->setChecked(false);

        gridLayout->addWidget(baidu_Button, 5, 1, 1, 1);

        loadButton = new QPushButton(gridLayoutWidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        gridLayout->addWidget(loadButton, 1, 1, 1, 1);

        downloadButton = new QPushButton(gridLayoutWidget);
        downloadButton->setObjectName(QString::fromUtf8("downloadButton"));

        gridLayout->addWidget(downloadButton, 2, 1, 1, 1);

        resetButton = new QPushButton(gridLayoutWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        gridLayout->addWidget(resetButton, 2, 3, 1, 1);

        delimiter = new QLabel(gridLayoutWidget);
        delimiter->setObjectName(QString::fromUtf8("delimiter"));
        delimiter->setMidLineWidth(0);

        gridLayout->addWidget(delimiter, 0, 0, 11, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 2, 2, 1);

        editButton = new QPushButton(gridLayoutWidget);
        editButton->setObjectName(QString::fromUtf8("editButton"));

        gridLayout->addWidget(editButton, 1, 3, 1, 1);

        calculateButton = new QPushButton(gridLayoutWidget);
        calculateButton->setObjectName(QString::fromUtf8("calculateButton"));

        gridLayout->addWidget(calculateButton, 9, 1, 1, 3);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 8, 1, 1, 3);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setRowStretch(3, 1);
        gridLayout->setRowStretch(4, 2);
        gridLayout->setRowStretch(5, 1);
        gridLayout->setRowStretch(6, 1);
        gridLayout->setRowStretch(7, 10);
        gridLayout->setRowStretch(8, 1);
        gridLayout->setRowStretch(9, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 10);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 10);
        gridLayout->setColumnStretch(4, 1);

        gridLayoutBody->addLayout(gridLayout, 0, 1, 2, 1);

        gridLayoutBody->setRowStretch(0, 1);
        gridLayoutBody->setRowStretch(1, 1);
        gridLayoutBody->setColumnStretch(0, 618);
        gridLayoutBody->setColumnStretch(1, 382);
        View->setCentralWidget(centralwidget);
        titleMenuBar = new QMenuBar(View);
        titleMenuBar->setObjectName(QString::fromUtf8("titleMenuBar"));
        titleMenuBar->setGeometry(QRect(0, 0, 960, 26));
        View->setMenuBar(titleMenuBar);

        retranslateUi(View);

        QMetaObject::connectSlotsByName(View);
    } // setupUi

    void retranslateUi(QMainWindow *View)
    {
        View->setWindowTitle(QCoreApplication::translate("View", "View", nullptr));
        latexLabel->setText(QCoreApplication::translate("View", "latex_Label", nullptr));
        imgLabel->setText(QCoreApplication::translate("View", "img_Label", nullptr));
        imgInfo->setPlainText(QCoreApplication::translate("View", "IMG_INFO", nullptr));
        label_2->setText(QCoreApplication::translate("View", "-----------Formula Recognizer-----------", nullptr));
        label_3->setText(QString());
        label_7->setText(QString());
        label_4->setText(QCoreApplication::translate("View", "-----------------Button-----------------", nullptr));
        mathpixButton->setText(QCoreApplication::translate("View", "Mathpix", nullptr));
        baidu_Button->setText(QCoreApplication::translate("View", "Baidu", nullptr));
        loadButton->setText(QCoreApplication::translate("View", "Load", nullptr));
        downloadButton->setText(QCoreApplication::translate("View", "Download", nullptr));
        resetButton->setText(QCoreApplication::translate("View", "Reset", nullptr));
        delimiter->setText(QString());
        label->setText(QString());
        editButton->setText(QCoreApplication::translate("View", "Edit", nullptr));
        calculateButton->setText(QCoreApplication::translate("View", "Calculate", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class View: public Ui_View {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_H

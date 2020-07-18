/********************************************************************************
** Form generated from reading UI file 'view.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_View
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QGridLayout *gridLayoutBody;
    QLabel *imgLabel;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QPushButton *loadButton;
    QPushButton *downloadButton;
    QLabel *label_6;
    QPushButton *applyButton;
    QLabel *label_13;
    QLabel *label_3;
    QPushButton *resetButton;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_5;
    QLabel *delimiter;
    QLabel *label_9;
    QPushButton *prettifyButton;
    QPushButton *editButton;
    QLabel *label_8;
    QPushButton *calculateButton;
    QLabel *label_4;
    QTextEdit *imgInfo;
    QLabel *latexLabel;
    QMenuBar *titleMenuBar;

    void setupUi(QMainWindow *View)
    {
        if (View->objectName().isEmpty())
            View->setObjectName(QString::fromUtf8("View"));
        View->resize(960, 626);
        centralwidget = new QWidget(View);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(0);
        formLayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutBody = new QGridLayout();
        gridLayoutBody->setObjectName(QString::fromUtf8("gridLayoutBody"));
        gridLayoutBody->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayoutBody->setVerticalSpacing(0);
        imgLabel = new QLabel(centralwidget);
        imgLabel->setObjectName(QString::fromUtf8("imgLabel"));
        sizePolicy.setHeightForWidth(imgLabel->sizePolicy().hasHeightForWidth());
        imgLabel->setSizePolicy(sizePolicy);

        gridLayoutBody->addWidget(imgLabel, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 4, 1, 1, 3);

        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        sizePolicy.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(loadButton, 2, 1, 1, 1);

        downloadButton = new QPushButton(centralwidget);
        downloadButton->setObjectName(QString::fromUtf8("downloadButton"));
        sizePolicy.setHeightForWidth(downloadButton->sizePolicy().hasHeightForWidth());
        downloadButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(downloadButton, 7, 1, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_6, 8, 1, 1, 3);

        applyButton = new QPushButton(centralwidget);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));
        sizePolicy.setHeightForWidth(applyButton->sizePolicy().hasHeightForWidth());
        applyButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(applyButton, 6, 3, 1, 1);

        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_13, 0, 1, 1, 3);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_3, 12, 1, 1, 3);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        sizePolicy.setHeightForWidth(resetButton->sizePolicy().hasHeightForWidth());
        resetButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(resetButton, 2, 3, 1, 1);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_10, 7, 2, 1, 1);

        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_11, 2, 2, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 6, 2, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_7, 0, 4, 13, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_5, 10, 1, 1, 3);

        delimiter = new QLabel(centralwidget);
        delimiter->setObjectName(QString::fromUtf8("delimiter"));
        sizePolicy.setHeightForWidth(delimiter->sizePolicy().hasHeightForWidth());
        delimiter->setSizePolicy(sizePolicy);
        delimiter->setMidLineWidth(0);

        gridLayout->addWidget(delimiter, 0, 0, 13, 1);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_9, 3, 1, 1, 3);

        prettifyButton = new QPushButton(centralwidget);
        prettifyButton->setObjectName(QString::fromUtf8("prettifyButton"));
        sizePolicy.setHeightForWidth(prettifyButton->sizePolicy().hasHeightForWidth());
        prettifyButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(prettifyButton, 7, 3, 1, 1);

        editButton = new QPushButton(centralwidget);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        sizePolicy.setHeightForWidth(editButton->sizePolicy().hasHeightForWidth());
        editButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(editButton, 6, 1, 1, 1);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_8, 5, 1, 1, 3);

        calculateButton = new QPushButton(centralwidget);
        calculateButton->setObjectName(QString::fromUtf8("calculateButton"));
        sizePolicy.setHeightForWidth(calculateButton->sizePolicy().hasHeightForWidth());
        calculateButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(calculateButton, 11, 1, 1, 3);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 1, 1, 1, 3);

        imgInfo = new QTextEdit(centralwidget);
        imgInfo->setObjectName(QString::fromUtf8("imgInfo"));

        gridLayout->addWidget(imgInfo, 9, 1, 1, 3);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 2);
        gridLayout->setRowStretch(2, 2);
        gridLayout->setRowStretch(3, 1);
        gridLayout->setRowStretch(4, 2);
        gridLayout->setRowStretch(5, 1);
        gridLayout->setRowStretch(6, 2);
        gridLayout->setRowStretch(7, 2);
        gridLayout->setRowStretch(8, 1);
        gridLayout->setRowStretch(9, 10);
        gridLayout->setRowStretch(10, 1);
        gridLayout->setRowStretch(11, 2);
        gridLayout->setRowStretch(12, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 10);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 10);
        gridLayout->setColumnStretch(4, 1);

        gridLayoutBody->addLayout(gridLayout, 0, 1, 2, 1);

        latexLabel = new QLabel(centralwidget);
        latexLabel->setObjectName(QString::fromUtf8("latexLabel"));
        sizePolicy.setHeightForWidth(latexLabel->sizePolicy().hasHeightForWidth());
        latexLabel->setSizePolicy(sizePolicy);

        gridLayoutBody->addWidget(latexLabel, 1, 0, 1, 1);

        gridLayoutBody->setRowStretch(0, 1);
        gridLayoutBody->setRowStretch(1, 1);
        gridLayoutBody->setColumnStretch(0, 618);
        gridLayoutBody->setColumnStretch(1, 382);

        formLayout->setLayout(0, QFormLayout::FieldRole, gridLayoutBody);

        View->setCentralWidget(centralwidget);
        titleMenuBar = new QMenuBar(View);
        titleMenuBar->setObjectName(QString::fromUtf8("titleMenuBar"));
        titleMenuBar->setGeometry(QRect(0, 0, 960, 26));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(titleMenuBar->sizePolicy().hasHeightForWidth());
        titleMenuBar->setSizePolicy(sizePolicy1);
        View->setMenuBar(titleMenuBar);

        retranslateUi(View);

        QMetaObject::connectSlotsByName(View);
    } // setupUi

    void retranslateUi(QMainWindow *View)
    {
        View->setWindowTitle(QCoreApplication::translate("View", "View", nullptr));
        imgLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("View", "-----------Formula Recognizer-----------", nullptr));
        loadButton->setText(QCoreApplication::translate("View", "Load", nullptr));
        downloadButton->setText(QCoreApplication::translate("View", "Download", nullptr));
        label_6->setText(QString());
        applyButton->setText(QCoreApplication::translate("View", "Apply", nullptr));
        label_13->setText(QString());
        label_3->setText(QString());
        resetButton->setText(QCoreApplication::translate("View", "Reset", nullptr));
        label_10->setText(QString());
        label_11->setText(QString());
        label->setText(QString());
        label_7->setText(QString());
        label_5->setText(QString());
        delimiter->setText(QString());
        label_9->setText(QString());
        prettifyButton->setText(QCoreApplication::translate("View", "Prettify", nullptr));
        editButton->setText(QCoreApplication::translate("View", "Edit", nullptr));
        label_8->setText(QString());
        calculateButton->setText(QCoreApplication::translate("View", "Calculate", nullptr));
        label_4->setText(QCoreApplication::translate("View", "-----------------Button-----------------", nullptr));
        latexLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class View: public Ui_View {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_H

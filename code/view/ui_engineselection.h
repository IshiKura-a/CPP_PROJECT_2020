/********************************************************************************
** Form generated from reading UI file 'engineselection.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENGINESELECTION_H
#define UI_ENGINESELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EngineSelection
{
public:
    QFormLayout *formLayout;
    QGridLayout *engineSelectionGridLayout;
    QRadioButton *baiduRadioButton;
    QRadioButton *mathPixRadioButton;
    QLabel *label_5;

    void setupUi(QWidget *EngineSelection)
    {
        if (EngineSelection->objectName().isEmpty())
            EngineSelection->setObjectName(QString::fromUtf8("EngineSelection"));
        EngineSelection->resize(272, 219);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EngineSelection->sizePolicy().hasHeightForWidth());
        EngineSelection->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(EngineSelection);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(0);
        formLayout->setContentsMargins(0, 0, 0, 0);
        engineSelectionGridLayout = new QGridLayout();
        engineSelectionGridLayout->setSpacing(6);
        engineSelectionGridLayout->setObjectName(QString::fromUtf8("engineSelectionGridLayout"));
        engineSelectionGridLayout->setContentsMargins(50, 0, 50, 0);
        baiduRadioButton = new QRadioButton(EngineSelection);
        baiduRadioButton->setObjectName(QString::fromUtf8("baiduRadioButton"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(baiduRadioButton->sizePolicy().hasHeightForWidth());
        baiduRadioButton->setSizePolicy(sizePolicy1);

        engineSelectionGridLayout->addWidget(baiduRadioButton, 0, 0, 1, 1);

        mathPixRadioButton = new QRadioButton(EngineSelection);
        mathPixRadioButton->setObjectName(QString::fromUtf8("mathPixRadioButton"));
        sizePolicy1.setHeightForWidth(mathPixRadioButton->sizePolicy().hasHeightForWidth());
        mathPixRadioButton->setSizePolicy(sizePolicy1);
        mathPixRadioButton->setChecked(true);

        engineSelectionGridLayout->addWidget(mathPixRadioButton, 0, 2, 1, 1);

        label_5 = new QLabel(EngineSelection);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        engineSelectionGridLayout->addWidget(label_5, 0, 1, 1, 1);

        engineSelectionGridLayout->setRowStretch(0, 1);
        engineSelectionGridLayout->setColumnStretch(0, 5);
        engineSelectionGridLayout->setColumnStretch(1, 1);
        engineSelectionGridLayout->setColumnStretch(2, 5);

        formLayout->setLayout(0, QFormLayout::FieldRole, engineSelectionGridLayout);


        retranslateUi(EngineSelection);

        QMetaObject::connectSlotsByName(EngineSelection);
    } // setupUi

    void retranslateUi(QWidget *EngineSelection)
    {
        EngineSelection->setWindowTitle(QCoreApplication::translate("EngineSelection", "EngineSelection", nullptr));
        baiduRadioButton->setText(QCoreApplication::translate("EngineSelection", "Baidu", nullptr));
        mathPixRadioButton->setText(QCoreApplication::translate("EngineSelection", "Mathpix", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EngineSelection: public Ui_EngineSelection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENGINESELECTION_H

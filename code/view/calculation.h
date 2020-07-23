#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QSvgRenderer>
#include <QPainter>
#include <QDebug>
#include <QScrollBar>
#include "stylesheet.h"
#include "ui_calculation.h"
#include "../common/def.h"

class Calculation : public QWidget
{
	Q_OBJECT

public:
	Calculation(QWidget *parent = Q_NULLPTR);
	~Calculation(){}

    void initQLayout(ptr<QPixmap> latexFormulaPixmap);
    void setLatexFormulaImage(ptr<QPixmap> latexFormulaPixmap);
    void setCalculateLatexFormula(WorkFunction command)
    {
        calculateLatexFormula = command;
    }



    // Data-getter & setter setter
    void setVarValPairsGetter(const Getter<ptr<const QVector<VarValPair>>>& getter)
    {
        varValPairsGetter = getter;
    }
    void setVarValPairsSetter(const Setter<const QVector<VarValPair>>& setter)
    {
        varValPairsSetter = setter;
    }
    void setResultGetter(const Getter<ptr<const QString>>& getter)
    {
        resultGetter = getter;
    }


    // callback function
    void varValPairsUpdateNotified()
    {
        varValPairs = varValPairsGetter();
    }

    void resultViewUpdateNotified()
    {
        result = resultGetter();
    }
private slots:
    // void on_btn_Cal_clicked();//��Ӳۺ���,���ҰѲۺ�����Button���źź�����������

private:
    Ui::Calculation* ui;
    

    // data
    ptr<const QVector<VarValPair>> varValPairs;
    ptr<const QString> result;

    // �ؼ�
    ptr<QLineEdit> varLineEdit;
    ptr<QLineEdit> valLineEdit;
    ptr<QLineEdit> answerLineEdit;
    ptr<QSpinBox> precisionSpinBox;
    ptr<QPushButton> addButton;
    ptr<QPushButton> computionButton;
    ptr<QPushButton> deleteLastButton;
    ptr<QLabel> titleLabel;
    ptr<QLabel> varLabel;
    ptr<QLabel> valLabel;
    ptr<QLabel> answerLabel;
    ptr<QLabel> imgLabel;
    ptr<QLabel> bitLabel;
    ptr<QLabel> precisionLabel;
    ptr<QVBoxLayout> scrollVBoxLayout;
    ptr<QTableWidget> varValSheetTable;
    ptr<QGridLayout> gridLayout;
    
    int tableRowCount;


    Getter<ptr<const QVector<VarValPair>>> varValPairsGetter;
    Setter<const QVector<VarValPair>> varValPairsSetter;
    Getter<ptr<const QString>> resultGetter;

    // ��̬�󶨺���
    WorkFunction calculateLatexFormula;
	
};

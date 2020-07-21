#ifndef VIEWCALCULATE_H
#define VIEWCALCULATE_H

#include <QMainWindow>
#include "../common/def.h"

namespace Ui {
class viewCalculate;
}

class viewCalculate : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewCalculate(QWidget *parent = 0);
    void setCalculateLatexFormula(WorkFunction command)
    {
        calculateLatexFormula = command;
    }

    ~viewCalculate();


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
    void on_btn_Cal_clicked();//添加槽函数,并且把槽函数和Button的信号函数关联起来

private:
    Ui::viewCalculate *ui;
    void initQVLayout();
    void on_lineEdit_returnPressed();

    ptr<const QVector<VarValPair>> varValPairs;
    ptr<const QString> result;

    Getter<ptr<const QVector<VarValPair>>> varValPairsGetter;
    Setter<const QVector<VarValPair>> varValPairsSetter;
    Getter<ptr<const QString>> resultGetter;

    // 动态绑定函数
    WorkFunction calculateLatexFormula;

};

#endif // VIEWCALCULATE_H

#ifndef VIEWCALCULATE_H
#define VIEWCALCULATE_H

#include <QMainWindow>

namespace Ui {
class viewCalculate;
}

class viewCalculate : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewCalculate(QWidget *parent = 0);
    ~viewCalculate();
private slots:
    void on_btn_Cal_clicked();//添加槽函数,并且把槽函数和Button的信号函数关联起来

private:
    Ui::viewCalculate *ui;
    void initQVLayout();
    void on_lineEdit_returnPressed();

};

#endif // VIEWCALCULATE_H

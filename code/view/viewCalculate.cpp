#include "viewCalculate.h"
#include "ui_viewCalculate.h"
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QCoreApplication>
#include <QString>
#include <QTextCodec>
#include <QFontMetrics>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include<QScrollArea>
#include <QLineEdit>

viewCalculate::viewCalculate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::viewCalculate)
{
    ui->setupUi(this);
	this->resize(QSize(800, 600));
	connect(this->ui->btn_Cal,SIGNAL(clicked(bool)),this,SLOT(on_btn_Cal_clicked()));
    QWidget * pWgt = new QWidget;

    QVBoxLayout *pLayout = new QVBoxLayout();//网格布局
    for(int i = 0; i < 100; i++)  //TODO : 把100替换为动态产生的参数个数
    {
        QLabel *pLab = new QLabel();
        QLineEdit *pLE =new QLineEdit() ;  //输入参数的文本框,除了分数还得解析pi e
        pLE->setText(QString("参数%1").arg(i));
        pLE->setMinimumSize(QSize(60,30));
        pLab->setText(QString("变量%1").arg(i));
        pLab->setMinimumSize(QSize(60,30));   //width height
        pLayout->addWidget(pLab);//把按钮添加到布局控件中
        pLayout->addWidget(pLE);
    }
    pWgt->setLayout(pLayout);
      //这一句setWidget必须放在pWgt里面的内容都准备完毕之后，否则显示有问题
     ui->textEdit->setReadOnly(true);// 可以复制答案,不能修改
     ui->scrollArea->setWidget(pWgt);
     qDebug() << "init success";
     //QLineEdit.textChanged(); // QLineEdit::editingFinished() [signal] 有这样一个信号,之后希望修改好精度.
}

viewCalculate::~viewCalculate()
{
    delete ui;
    qDebug() << "关闭输入变量窗口";
}

void viewCalculate::initQVLayout()
{
}


void viewCalculate::on_btn_Cal_clicked(){    //计算按钮
    qDebug() << "begin calculate";
    int accuracy = ui->spinBox->value();            //获取精度
    qDebug() <<"accrancy ="<< QString(accuracy);
    double result = accuracy;
    QString str = QString("精度为小数点后%1位,计算结果为%2").arg(accuracy).arg(result);
    ui->textEdit->setText(str);      //QPlainTextEdit 多行简单文本框用 toPlainText()；QTextEdit 富文本框，简单文本用toPlainText(), 富文本用 toHtml().QLineEdit 用 text().
    qDebug() << "the answer is"<<ui->textEdit->toPlainText();    //输出到debug里
}

#include "set_ui.h"
#include "ui_set_ui.h"
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


set_ui::set_ui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::set_ui)
{
    ui->setupUi(this);
    QWidget * pWgt = new QWidget;

    QVBoxLayout *pLayout = new QVBoxLayout();//网格布局
    for(int i = 0; i < 100; i++)
    {
        QPushButton *pBtn = new QPushButton();
        QLineEdit *pLE =new QLineEdit() ;  //输入参数的文本框
        pLE->setText(QString("参数%1").arg(i));
        pLE->setMinimumSize(QSize(60,30));
        pBtn->setText(QString("按钮%1").arg(i));
        pBtn->setMinimumSize(QSize(60,30));   //width height
        pLayout->addWidget(pBtn);//把按钮添加到布局控件中
        pLayout->addWidget(pLE);
    }
    pWgt->setLayout(pLayout);
      //这一句setWidget必须放在pWgt里面的内容都准备完毕之后，否则显示有问题
     ui->scrollArea->setWidget(pWgt);

}

set_ui::~set_ui()
{
    delete ui;
}

void set_ui::initQVLayout()
{

}

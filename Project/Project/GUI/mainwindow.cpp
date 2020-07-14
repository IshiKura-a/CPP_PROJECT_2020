#include "mainwindow.h"
#include "ui_mainwindow.h"
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


const QString urlBase = "https://latex.codecogs.com/svg.download?";
const QString latexFormulaAddr = "./latex_formula.svg";
QString latexFormula = "\\sigma(z)=\\frac{1}{1+e^{-z}}";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_clicked()));
    setFixedSize(800,600);
    img_Label = new QLabel;
    latex_Label = new QLabel;
    latex_Editor = new QPlainTextEdit;
    net_Manager = new QNetworkAccessManager;
    hLayout_Menu = new QHBoxLayout;
    title_MenuBar = new QMenuBar;
    gridLayout_Body = new QGridLayout;
    timer = new QTimer(this);

    latex_Label->installEventFilter(this);
    latex_Editor->installEventFilter(this);
    initQVLayout();

  //  QPushButton *pushButton = new QPushButton(this);// 按钮
   // pushButton->setText("new");  //设置名字
   // pushButton->setGeometry(400,150,200,20);

//   TextEdit1 =new QTextEdit(this);
//   TextEdit1->setGeometry(400,150,200,20);
//   TextEdit1->setAlignment(Qt::AlignCenter);

//   TextEdit2 =new QTextEdit(this);
//   TextEdit2->setGeometry(400,170,200,20);
//   TextEdit2->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenu()
{
    title_MenuBar->setFont(QFont("幼圆",10,QFont::Normal,false));
    QMenu* title_Menu[2];
    title_Menu[0] = title_MenuBar->addMenu("文件");

    QAction* act_Load = title_Menu[0]->addAction("导入");
    act_Load->setFont(QFont("幼圆",10,QFont::Normal,false));
    connect(act_Load, &QAction::triggered, [=](){
        QString img_Name = QFileDialog::getOpenFileName(
                    NULL,"打开文件( 推荐jpg文件 )","C:\\","图像文件(*.jpg *.jpeg *.png *.bmp)");
        qDebug() << "Load " + img_Name;
        img_Label->setPixmap(QPixmap(img_Name).scaled(img_Label->size(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation));
        latexDisplay();
    });

    QAction* act_exit = title_Menu[0]->addAction("关闭");
    act_exit->setFont(QFont("幼圆",10,QFont::Normal,false));
    connect(act_exit, &QAction::triggered, [=](){
        qDebug() << "Exit";
    });

    QAction* act_help = title_MenuBar->addAction("帮助");
    QString str("debug中帮助可以显示中文");
    act_help->setFont(QFont("幼圆",10,QFont::Normal,false));
    connect(act_help, &QAction::triggered, [=](){
        qDebug() << str;
    });
}
void MainWindow::initQVLayout()
{
    QVBoxLayout* vLayout = ui->verticalLayout;  //窗口界面的排列 ,QVBoxLayout：在竖直方向上排列窗口部件，从上到下。
    vLayout->addLayout(hLayout_Menu);   //首先加入菜单
    hLayout_Menu->setDirection(QBoxLayout::LeftToRight); //菜单排列是从左到右

    initMenu();//调用方法初始化菜单
    hLayout_Menu->addWidget(title_MenuBar);  //horizontally 水平的
    vLayout->setStretchFactor(hLayout_Menu,1); //设置窗口小部件的拉伸因子以进行拉伸，如果在此布局中找到窗口小部件（不包括子布局），则返回true；否则，返回true。 否则返回false。

    vLayout->addLayout(gridLayout_Body);  //body用grid
    vLayout->setStretchFactor(gridLayout_Body,19); //拉伸因子= 19
    initBody();


}

void MainWindow::createInput(){
    // 先创建右边的widget，用布局进行管理
    //QWidget *widgetMain = new QWidget();
//    QLineEdit *lineEdit = new QLineEdit(widgetMain);  //输入框
//  //  QHBoxLayout *horLayout = new QHBoxLayout();  //水平放置,用水平布局将这2个控件框起，并且置于界面顶部
 //   gridLayout_Body->addWidget(widgetMain,1,1);   // 加入一个输入框和按钮
//  //  horLayout->addWidget(lineEdit,4);
////    horLayout->addWidget(btn, 1);        // 设置布局比例为4:1

//    // 然后添加一个全局布局控件
//    QVBoxLayout *verLayout = new QVBoxLayout(widgetMain);
//    verLayout->addWidget(lineEdit,1);   //加入文字编辑
//    verLayout->addWidget(btn,1);      //在下面加入按钮
//    gridLayout_Body->addLayout(verLayout,1,1);

//   // verLayout->addLayout(horLayout);// 加入刚才的输入组，底部添加弹簧
//   // verLayout->addStretch();

////    int nCnt = lineEdit->text().toInt(); // 输入的个数
////    for (int i = 0; i < nCnt; i++) {
////    QLabel *label = new QLabel(widgetMain);    // 插入之前的布局
////    label->setText(QString("动态创建label%1").arg(i + 1)); // i+1 替换第一个变量%1, 如果还有变量就%2 %3 .
////    verLayout->insertWidget(1 + i, label);
////    }
}

void MainWindow::latexDisplay()
{
    QUrl url = QUrl(urlBase + latexFormula);
    qDebug() << "Getting " + url.url();
    connect(net_Manager, SIGNAL(finished(QNetworkReply*)),this,
            SLOT(displayPic4Url(QNetworkReply*)));
    QNetworkRequest request;
    request.setUrl(url);
    net_Manager->get(request);
}
void MainWindow::displayPic4Url(QNetworkReply *reply)
{

    if(reply->error() == QNetworkReply::NoError)  //打开svg文件
    {
        qDebug() << "Downloading...";
        QByteArray data_bytes = reply->readAll();
        QFile file(latexFormulaAddr);
        file.open(QIODevice::ReadWrite);
        file.write(data_bytes);
    }
    reply->deleteLater();

    QSvgRenderer* svg = new QSvgRenderer(latexFormulaAddr);  //用来画SVG文件内容到paint device,Used to draw the contents of SVG files onto paint devices
    qDebug() << svg->defaultSize();

    int width = svg->defaultSize().width() * 2;
    if(width >= 400) width = 400;
    int height = svg->defaultSize().height()*2;
    if(height >= 285) height = 285;

    QPixmap* img =new QPixmap(width,height);
    img->fill(Qt::white);
    QPainter painter(img);
    svg->render(&painter);


    latex_Label->setPixmap(*img);
    latex_Label->setAlignment(Qt::AlignCenter);

}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "打开输入变量窗口";
    set_ui* d =new set_ui()  ;
    d->show();
    d->setWindowTitle("输入变量");

}
void MainWindow::initBody()
{

    img_Label->setStyleSheet("background: #7BD9D2");
    img_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout_Body->addWidget(img_Label,0,0);

    latex_Editor->setPlainText(latexFormula);
    latex_Editor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    latex_Editor->setFont(QFont("Courier New",14,QFont::Normal,false));
    qDebug() << "latex_Editor: " + latex_Editor->toPlainText();
    gridLayout_Body->addWidget(latex_Editor,1,0);


    latex_Label->setStyleSheet("background: #FFFFFF");
    latex_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout_Body->addWidget(latex_Label,1,0);

    gridLayout_Body->setRowStretch(0,1);
    gridLayout_Body->setRowStretch(1,1);
    gridLayout_Body->setColumnStretch(0,1);
    gridLayout_Body->setColumnStretch(1,1);
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    connect(timer,SIGNAL(timeout()),this,SLOT(changeLatexLayout()));
    if(obj == latex_Label)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            qDebug() << "Click on latex_Label";
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

            if(mouseEvent->button() == Qt::LeftButton)
            {
                latex_Label->setHidden(true);
                latex_Editor->setHidden(false);  //隐藏编辑器
                return true;
            }else return false;
        }else return false;
    }
    else if(obj == latex_Editor)
    {
        if(event->type() == QEvent::Leave)
        {
            timer->start(1000);
        }else
            timer->stop();
        return false;
    }
    else return QWidget::eventFilter(obj, event);
}

void MainWindow::changeLatexLayout()
{
    if(latex_Label->isHidden())
    {
        qDebug() << "Hide latex_Editor";
        latex_Label->setHidden(false);
        latex_Editor->setHidden(true);

        if(latexFormula != (latex_Editor->document())->toPlainText())
        {
            qDebug() << "Text changed.";
            latexFormula = (latex_Editor->document())->toPlainText();
            latexDisplay();
        }
    }
}

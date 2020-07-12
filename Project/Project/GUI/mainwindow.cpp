#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QLabel>


const QString urlBase = "https://latex.codecogs.com/svg.download?";
const QString latexFormulaAddr = "./latex_formula.svg";
QString latexFormula = "\\sigma(z)=\\frac{1}{1+e^{-z}}";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    act_help->setFont(QFont("幼圆",10,QFont::Normal,false));
    connect(act_help, &QAction::triggered, [=](){
        qDebug() << "Help";
    });
}
void MainWindow::initQVLayout()
{
    QVBoxLayout* vLayout = ui->verticalLayout;


    vLayout->addLayout(hLayout_Menu);
    hLayout_Menu->setDirection(QBoxLayout::LeftToRight);

    initMenu();
    hLayout_Menu->addWidget(title_MenuBar);
    vLayout->setStretchFactor(hLayout_Menu,1);

    vLayout->addLayout(gridLayout_Body);
    vLayout->setStretchFactor(gridLayout_Body,19);

    initBody();
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

    if(reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "Downloading...";
        QByteArray data_bytes = reply->readAll();
        QFile file(latexFormulaAddr);
        file.open(QIODevice::ReadWrite);
        file.write(data_bytes);
    }
    reply->deleteLater();

    QSvgRenderer* svg = new QSvgRenderer(latexFormulaAddr);
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
                latex_Editor->setHidden(false);
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

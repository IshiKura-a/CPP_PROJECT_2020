#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
    gridLayout_Body = ptr<QGridLayout>(ui->gridLayout_Body);
    title_MenuBar = ptr<QMenuBar>(ui->title_MenuBar);

    img_Label = std::make_shared<QLabel>();
    latex_Label = std::make_shared<QLabel>();
    latex_Formula = std::make_shared<std::string>("");
    latex_Editor = std::make_shared<QPlainTextEdit>();
    initQLayout();
}

View::~View()
{
    delete ui;
}

void View::initQLayout()
{
    setFixedSize(800,600);
    initMenu();
    initBody();
}

void View::initMenu()
{
    title_MenuBar->setFont(QFont("幼圆",10,QFont::Normal,false));

    QMenu* File;
    File = (title_MenuBar->addMenu("文件"));

    // 设置文件菜单下有导入、关闭功能
    QAction* act_Load = (File->addAction("导入"));
    act_Load->setFont(QFont("幼圆",10,QFont::Normal,false));
    connect(act_Load, &QAction::triggered, [=](){

        if(loadImg4Dir)
        {
            qDebug() << "Load";
            loadImg4Dir();
        }
        else
        {
            qDebug() << "No load available.";
        }

    });

    QAction* act_Exit = (File->addAction("关闭"));
    act_Exit->setFont(QFont("幼圆",10,QFont::Normal,false));
    connect(act_Exit, &QAction::triggered, [=](){
        exit(0);
        qDebug() << "Quit";
    });

    // 帮助
    QAction* act_help = (title_MenuBar->addAction("帮助"));
    act_help->setFont(QFont("幼圆",10,QFont::Normal,false));
    connect(act_help, &QAction::triggered, [=](){

        if(displayHelpDocument)
        {
            qDebug() << "Help";
            displayHelpDocument();
        }
        else
        {
            qDebug() << "No help available.";
        }

    });

}

void View::initBody()
{
    img_Label->setStyleSheet("background: #7BD9D2");
    // img_Label->setHidden(true);
    img_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout_Body->addWidget(img_Label.get(),0,0);

    if (!latex_Formula->empty())
    {
        latex_Editor->setPlainText(latex_Formula->c_str());
        latex_Editor->setFont(QFont("Courier New", 14, QFont::Normal, false));
        qDebug() << "latex_Editor: " + latex_Editor->toPlainText();
    }
    else
    {
        latex_Editor->clear();
        qDebug() << "latex_Editor is empty.";
    }
    latex_Editor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    gridLayout_Body->addWidget(latex_Editor.get(),1,0);


    latex_Label->setStyleSheet("background: #FFFFFF");
    latex_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout_Body->addWidget(latex_Label.get(),1,0);
    // latex_Label->setHidden(true);
    gridLayout_Body->setRowStretch(0,1);
    gridLayout_Body->setRowStretch(1,1);
    gridLayout_Body->setColumnStretch(0,1);
    gridLayout_Body->setColumnStretch(1,1);
}


void View::onChangeLatexFormula()
{
    qDebug() << "Change Latex formula";
}

void View::setImgLabel(ptr<QLabel> iLabel)
{
    img_Label = iLabel;
}
void View::setLatexLabel(ptr<QLabel> iLabel)
{
    latex_Label = iLabel;
}
void View::setLatexEditor(ptr<QPlainTextEdit> iPlainTextEdit)
{
    latex_Editor = iPlainTextEdit;
}
void View::setLatexFormula(ptr<std::string> iString)
{
    latex_Formula = iString;
}

auto View::getImgLabel()
{
    return img_Label;
}
auto View::getLatexLabel()
{
    return latex_Label;
}
auto View::getLatexEditor()
{
    return latex_Editor;
}
auto View::getLatexFormula()
{
    return latex_Formula;
}

auto View::getGridLayoutBody()
{
    return gridLayout_Body;
}
auto View::getTitleMenuBar()
{
    return title_MenuBar;
}


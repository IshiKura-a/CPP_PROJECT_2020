#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
    setWindowTitle("Welcome!");
    gridLayoutBody = ptr<QGridLayout>(ui->gridLayoutBody);
    titleMenuBar = ptr<QMenuBar>(ui->titleMenuBar);
    imgLabel = ptr<QLabel>(ui->imgLabel);
    latexLabel = ptr<QLabel>(ui->latexLabel);
    
    
    
    loadButton = ptr<QPushButton>(ui->loadButton);
    editButton = ptr<QPushButton>(ui->editButton);
    downloadButton = ptr<QPushButton>(ui->downloadButton);
    resetButton = ptr<QPushButton>(ui->resetButton);
    calculateButton = ptr<QPushButton>(ui->calculateButton);
    applyButton = ptr<QPushButton>(ui->applyButton);
    prettifyButton = ptr<QPushButton>(ui->prettifyButton);

    imgInfo = ptr<QTextEdit>(ui->imgInfo);
}

View::~View()
{
    delete ui;
}

void View::initQLayout()
{
    // setFixedSize(960,600);
    setMinimumSize(QSize(960, 615));
    setContentsMargins(0, 0, 0, 0);
    
    latexLabel->installEventFilter(this);
    latexEditor->installEventFilter(this);
    initMenu();
    initBody();
}

void View::initMenu()
{
    titleMenuBar->setFont(menuNormal);

    QMenu* File;
    File = (titleMenuBar->addMenu("文件"));

    // 设置文件菜单下有导入、关闭功能
    QAction* actLoad = (File->addAction("导入"));
    actLoad->setFont(menuNormal);
    connect(actLoad, SIGNAL(triggered()), SLOT(onClickLoadButton()));

    QAction* actExit = (File->addAction("关闭"));
    actExit->setFont(menuNormal);
    connect(actExit, &QAction::triggered, [=](){
        exit(0);
        qDebug() << "Quit";
        displayMsg("Quit");
    });

    // 帮助
    QAction* actHelp = (titleMenuBar->addAction("帮助"));
    actHelp->setFont(menuNormal);
    connect(actHelp, &QAction::triggered, [=](){

        if(displayHelpDocument)
        {
            qDebug() << "Help";
            displayMsg("Help");
            displayHelpDocument();
        }
        else
        {
            qDebug() << "No help available.";
            displayErrorMsg("No help available!");
        }

    });

}

void View::initBody()
{
    gridLayoutBody->setContentsMargins(0, 0, 0, 0);
    gridLayoutBody->setVerticalSpacing(0);
    imgLabel->setStyleSheet(lightBlueBackground + whiteWords + blackBorder2Px + noBottomBorder);
    imgLabel->setText("No image loaded");
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setFont(titleBold);
    // imgLabel->setHidden(true);
    imgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayoutBody->addWidget(imgLabel.get(),0,0);

    if (latexFormula && !latexFormula->empty())
    {
        latexEditor->setPlainText(QString(latexFormula->c_str()));
        qDebug() << "latexEditor: " + latexEditor->toPlainText();
    }
    else
    {
        latexEditor->setPlainText("Please input latex formula...");
        qDebug() << "latexEditor is empty.";
    }
    latexEditor->setFont(textNormal);

    latexEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    latexEditor->setHidden(true);

    gridLayoutBody->addWidget(latexLabel.get(), 1, 0);
    gridLayoutBody->addWidget(latexEditor.get(), 1, 0);


    latexLabel->setStyleSheet(whiteBackground + blackBorder2Px);
    latexLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    latexLabel->setText("No formula to render");
    latexLabel->setFont(titleBold);
    latexLabel->setAlignment(Qt::AlignCenter);
    
    
    QMainWindow::setStatusBar(statusBar.get());
    statusBar->setFont(msgNormal);
    statusBar->setStyleSheet(lightDarkBackground + whiteWords);
    displayMsg("Hello", 4000);


    initCmdInterface();
}

void View::initCmdInterface()
{
    // 绑定按钮事件
    connect(loadButton.get(), SIGNAL(clicked()), this, SLOT(onClickLoadButton()));

    
    connect(resetButton.get(), &QPushButton::clicked, [=]() {
        if (resetInterface)
        {
            qDebug() << "Reset";
            displayMsg("Reset");
            // resetInterface();
        }
        else
        {
            qDebug() << "No reset function";
            displayErrorMsg("No reset function!");
        }
    });
    connect(editButton.get(), &QPushButton::clicked, [=]() {
        if (editLatexFormula)
        {
            qDebug() << "Edit";
            displayMsg("Edit");

            // editLatexFormula();
        }
        else
        {
            qDebug() << "No edit function";
            displayErrorMsg("No edit function!");
        }
    });
    connect(applyButton.get(), &QPushButton::clicked, this, [=]() {
        if (applyLatexFormulaChanges)
        {
            qDebug() << "Apply changes";
            displayMsg("Apply changes");
        }
        else
        {
            qDebug() << "No apply function";
            displayErrorMsg("No apply function!");
        }
    });
    connect(downloadButton.get(), &QPushButton::clicked, [=]() {
        if (downloadRenderedLatexImg)
        {
            qDebug() << "Download";
            displayMsg("Download");
        }
        else
        {
            qDebug() << "No download function";
            displayErrorMsg("No download function!");
        }
    });
    connect(prettifyButton.get(), &QPushButton::clicked, [=]() {
        if (prettifyLatexFormula)
        {
            qDebug() << "Prettify";
            displayMsg("Prettify");
        }
        else
        {
            qDebug() << "No prettify function";
            displayErrorMsg("No prettify function!");
        }
    });
    connect(calculateButton.get(), &QPushButton::clicked, [=]() {
        if (calculateLatexFormula)
        {
            qDebug() << "Calculate";
            displayMsg("Calculate");
        }
        else
        {
            qDebug() << "No calculate function";
            displayErrorMsg("No calculate function!");
        }
    });
    
    // 设置图片信息属性
    imgInfo->setReadOnly(true);
    imgInfo->setText("No image loaded");
    imgInfo->setFont(textNormal);
    imgInfo->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

}

void View::onChangeLatexFormula()
{
    qDebug() << "Change Latex formula";
}

void View::setLatexEditor(ptr<QPlainTextEdit> iPlainTextEdit)
{
    latexEditor = iPlainTextEdit;
}
//void View::setLatexFormula(std::string iString)
//{
    //latexFormula->clear();
    //latexFormula->append(iString.c_str());
//}
void View::setStatusBar(ptr<QStatusBar> iStatusBar)
{
    statusBar = iStatusBar;
}
void View::setLatexFormula(ptr<const std::string> iString)
{
    latexFormula = iString;
}
void View::setTimer(ptr<QTimer> iTimer)
{
    timer = iTimer;
}
auto View::getImgLabel()
{
    return imgLabel;
}
auto View::getLatexLabel()
{
    return latexLabel;
}
auto View::getLatexEditor()
{
    return latexEditor;
}
auto View::getLatexFormula()
{
    return latexFormula;
}
auto View::getTimer()
{
    return timer;
}

auto View::getGridLayoutBody()
{
    return gridLayoutBody;
}
auto View::getTitleMenuBar()
{
    return titleMenuBar;
}
auto View::getStatusBar()
{
    return statusBar;
}

bool View::eventFilter(QObject* watched, QEvent* event)
{
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(onChangeLatexDisplay()));
    if (watched == latexLabel.get())
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            qDebug() << "Click on latexLabel";
            displayMsg("Click on latexLabel");
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

            if (mouseEvent->button() == Qt::LeftButton)
            {
                latexLabel->setHidden(true);
                latexEditor->setHidden(false);
                return false;
            }
            else return false;
        }
        else return false;
    }
    else if (watched == latexEditor.get())
    {
        qDebug() << event->type();
        if (event->type() == QEvent::Leave)
        {
            timer->start(500);
        }
        else
        {
            timer->stop();
        }
        return false;
    }
    else return QWidget::eventFilter(watched, event);
}

void View::onChangeLatexDisplay()
{
    if (latexLabel->isHidden())
    {

        qDebug() << latexFormula.get();
        qDebug() << latexEditor->document()->toPlainText();
        if (latexFormula && latexFormula.get()->data() != (latexEditor->document())->toPlainText())
        {
            qDebug() << "Text changed.";
            displayMsg("Text changed");
            //setLatexFormula(latexEditor->document()->toPlainText().toStdString());
            if(displayLatexFormula)
            {
                qDebug() << "Display latex formula";
                displayMsg("Display latex formula");
                displayLatexFormula();
            }
            else
            {
                displayErrorMsg("No latex formula display function!");
                qDebug() << "No latex formula display";
            }
        }

        qDebug() << "Hide latexEditor";
        displayMsg("Hide latexEditor");
        latexLabel->setHidden(false);
        latexEditor->setHidden(true);

    }
    else
    {
        //setLatexFormula(latexEditor->document()->toPlainText().toStdString());
    }
}

void View::displayMsg(std::string msg, int duration)
{
    statusBar->setStyleSheet(lightDarkBackground + whiteWords);
    if (duration == 0)
        statusBar->showMessage(msg.c_str());
    else
        statusBar->showMessage(msg.c_str(), duration);
}
void View::displayErrorMsg(std::string errorMsg)
{
    statusBar->setStyleSheet(lightDarkBackground + redWords);
    statusBar->showMessage(errorMsg.c_str());
}

void View::onClickLoadButton()
{
    imgLabel->setText("");
    if (loadImg4Dir)
    {
        qDebug() << "Load";
        displayMsg("Load");
        //loadImg4Dir();
    }
    else
    {
        displayErrorMsg("No load available!");
        qDebug() << "No load available.";
    }
}
#include "view.h"
#include "ui_view.h"
#include <Windows.h>

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
    globalFunctionalZoneLabel = ptr<QLabel>(ui->globalFunctionalZoneLabel);
    formulaDealerZoneLabel = ptr<QLabel>(ui->formulaDealerZoneLabel);
    
    
    
    loadButton = ptr<QPushButton>(ui->loadButton);
    editButton = ptr<QPushButton>(ui->editButton);
    downloadButton = ptr<QPushButton>(ui->downloadButton);
    resetButton = ptr<QPushButton>(ui->resetButton);
    calculateButton = ptr<QPushButton>(ui->calculateButton);
    applyButton = ptr<QPushButton>(ui->applyButton);
    prettifyButton = ptr<QPushButton>(ui->prettifyButton);

    imgInfo = ptr<QTextEdit>(ui->imgInfo);
    latexFormulaPixmap = std::make_shared<QPixmap>(getAdaptedSize(580, 286));
}

View::~View()
{
    delete ui;
}

void View::initQLayout()
{
    installFont();
    screenSize = getAdaptedSize(960, 600);
    imgSizeLimit = QSize((int)(screenSize.width() * 0.618 * 0.8), (int)(screenSize.height() * 0.4));
    setMinimumSize(screenSize);
    setContentsMargins(0, 0, 0, 0);
    
    latexLabel->installEventFilter(this);
    latexEditor->installEventFilter(this);
    engineSelectionInterface->installEventFilter(this);

    initMenu();
    initBody();
    engineSelectionInterface->initQLayout();
    // calculateInterface->initQLayout(latexFormulaPixmap);
}

void View::initMenu()
{
    titleMenuBar->setFont(menuNormal);
    titleMenuBar->setStyleSheet(":item" + hoverBlackWords + "QMenu,QMenuBar{" + whiteWords + "}");
    

    QMenu* file;
    file = (titleMenuBar->addMenu("文件"));

    // 设置文件菜单下有导入、下载、关闭功能
    QAction* actLoad = (file->addAction("导入\tCtrl O"));
    actLoad->setFont(menuNormal);
    connect(actLoad, SIGNAL(triggered()), SLOT(onClickLoadButton()));

    QAction* actDownload = (file->addAction("下载\tCtrl S"));
    actDownload->setFont(menuNormal);
    connect(actDownload, SIGNAL(triggered()), SLOT(onClickDownloadButton()));

    QAction* actExit = (file->addAction("关闭\tEsc"));
    actExit->setFont(menuNormal);
    actExit->setShortcut(Qt::Key_Escape);
    connect(actExit, &QAction::triggered, [=]() {
        exit(0);
        qDebug() << "Quit";
        displayMsg("Quit");
        });

    // 设置
    QMenu* settings = titleMenuBar->addMenu("设置");
    QAction* actSetRecognizeEngine = settings->addAction("设置识别引擎");
    actSetRecognizeEngine->setFont(menuNormal);
    connect(actSetRecognizeEngine, &QAction::triggered, [=]() {
        engineSelectionInterface->show();
        qDebug() << "Set Recognize Engine";
        displayMsg("Set Recognize Engine");
        });

    // 帮助
    QAction* actHelp = (titleMenuBar->addAction("帮助"));
    actHelp->setFont(menuNormal);
    connect(actHelp, &QAction::triggered, [=]() {
        displayMsg("Help");
        helpMsgBox->show();        
        });

    std::string helpText = std::any_cast<std::string>(displayHelpDocument());

    helpMsgBox->setText(helpText.c_str());
    helpMsgBox->setWindowTitle("Help");
    helpMsgBox->setStyleSheet(background4Img + whiteWords + "qproperty-alignment: AlignCenter;");
    helpMsgBox->setFont(textNormal);
    helpMsgBox->setButtonText(QMessageBox::Ok, "Visit Website");
    // helpMsgBox->setTextFormat(QTextFormat(QTextFormat::TextVerticalAlignment));
    helpMsgBox->button(QMessageBox::Ok)->setFont(msgNormal);

    QMargins margin = QMargins();
    margin.setTop(20);
    helpMsgBox->setContentsMargins(margin);
    connect(helpMsgBox->button(QMessageBox::Ok), &QPushButton::clicked, [=]()
        {
            QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/IshiKura-a/CPP_PROJECT_2020")));
        });
}

void View::initBody()
{
    setStyleSheet(background4Img);
    gridLayoutBody->setContentsMargins(0, 0, 0, 0);
    gridLayoutBody->setVerticalSpacing(0);
    imgLabel->setStyleSheet(whiteBackground + blackWords + blackBorder2Px + noBottomBorder);
    imgLabel->setText("No image loaded");
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setFont(titleBold);
    // imgLabel->setHidden(true);
    imgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayoutBody->addWidget(imgLabel.get(),0,0);

    formulaDealerZoneLabel->setFont(labelTextNormal);
    formulaDealerZoneLabel->setStyleSheet(transparentBackground + whiteWords);
    globalFunctionalZoneLabel->setFont(labelTextNormal);
    globalFunctionalZoneLabel->setStyleSheet(transparentBackground + whiteWords);

    if (latexString && !latexString->isEmpty())
    {
        latexEditor->setPlainText(*latexString);
        qDebug() << "latexEditor: " + latexEditor->toPlainText();
    }
    else
    {
        latexEditor->setPlainText("");
        qDebug() << "latexEditor is empty.";
    }
    latexEditor->setFont(textNormal);
    latexEditor->setStyleSheet(transparentBackground + whiteWords);

    latexEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    latexEditor->setHidden(true);

    gridLayoutBody->addWidget(latexLabel.get(), 1, 0);
    gridLayoutBody->addWidget(latexEditor.get(), 1, 0);


    latexLabel->setStyleSheet(transparentBackground + blackBorder2Px + whiteWords);
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
    // Shortcut: ctrl + o
    loadButton->setShortcut(Qt::CTRL + Qt::Key_O);
    loadButton->setFont(labelTextNormal);
    loadButton->setStyleSheet(whiteBackground + blackWords);
    
    connect(resetButton.get(), &QPushButton::clicked, [=]() {
        displayMsg("Reset");
        imgLabel->clear();
        imgLabel->setText("No image loaded");
        latexLabel->clear();
        latexLabel->setText("No formula to render");
        latexEditor->clear();
        setLatexString("");
        imgInfo->setText("No image loaded");
        imgInfo->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    });
    resetButton->setFont(labelTextNormal);
    resetButton->setStyleSheet(whiteBackground + blackWords);

    connect(editButton.get(), &QPushButton::clicked, [=]() {
        latexLabel->setHidden(true);
        latexEditor->setHidden(false); //显示编辑器,隐藏label
    });
    editButton->setFont(labelTextNormal);
    editButton->setStyleSheet(whiteBackground + blackWords);

    connect(applyButton.get(), &QPushButton::clicked, this, [=]() {
        onChangeLatexDisplay();
    });
    applyButton->setFont(labelTextNormal);
    applyButton->setStyleSheet(whiteBackground + blackWords);

    connect(downloadButton.get(), SIGNAL(clicked()), this, SLOT(onClickDownloadButton()));
    downloadButton->setShortcut(Qt::CTRL + Qt::Key_S);
    downloadButton->setFont(labelTextNormal);
    downloadButton->setStyleSheet(whiteBackground + blackWords);

	//连接美化按钮
    connect(prettifyButton.get(), &QPushButton::clicked, [=]() {
        // TO DO
        if (prettifyLatexFormula)
        {
            qDebug() << "Prettify";
            displayMsg("Prettify");
            prettifyLatexFormula();
            latexEditor->setPlainText(*latexString);
        }
        else
        {
            qDebug() << "No prettify function";
            displayErrorMsg("No prettify function!");
        }
    });
    prettifyButton->setFont(labelTextNormal);
    prettifyButton->setStyleSheet(whiteBackground + blackWords);

	//连接计算按钮
    connect(calculateButton.get(), &QPushButton::clicked, [=]() {

        if (imageData->isEmpty())
        {
            displayErrorMsg("No formula to calculate!");
        }
        else
        {
            displayMsg("Calculate Latex Formula");
            qDebug() << "Calculate Latex Formula";
            onClickCalculateButton();
        }
        });
    calculateButton->setFont(labelTextNormal);
    calculateButton->setStyleSheet(whiteBackground + blackWords);
    
    // 设置图片信息属性
    imgInfo->setReadOnly(true);
    imgInfo->setText("No image loaded");
    imgInfo->setFont(textNormal);
    imgInfo->setStyleSheet(whiteBackground + blackWords);
    imgInfo->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

}

void View::onChangeLatexFormula()
{
    const std::string imgType = "png";
    qDebug() << "Text changed." + latexEditor->document()->toPlainText();
    displayMsg("Text changed");
    setLatexString(latexEditor->document()->toPlainText());


    if (renderLatexString)
    {
        qDebug() << "Render latex formula";
        // displayMsg("Rendering",0);

        QSvgRenderer* svg = new QSvgRenderer;
        QImage* img = new QImage;
        int width, height;

        int cnt = 0;
        do {
            if (cnt++ >= 2)
            {
                displayErrorMsg(imageData->constData());
                return;
            }
            renderLatexString(imgType);

            qDebug() << imageData->isEmpty();
            qDebug() << imageData->constData();

        } while (!(imgType == "svg" && svg->load(*imageData)) && !(imgType != "svg" && img->loadFromData(*imageData)));

        if (imgType == "svg")
        {
            displayMsg("Success!");
            qDebug() << svg->defaultSize();

            width = svg->defaultSize().width();
            height = svg->defaultSize().height();

            if ((height * imgSizeLimit.width() / width) <= imgSizeLimit.height())
            {
                height = (height * imgSizeLimit.width() / width);
                width = imgSizeLimit.width();
            }
            else
            {
                width = (width * imgSizeLimit.height()) / height;
                height = imgSizeLimit.height();
            }

            // Here's a segmental fault remaining to be solved.
            latexFormulaPixmap->fill(Qt::transparent);
            QPainter painter(latexFormulaPixmap.get());
            svg->render(&painter);

            *latexFormulaPixmap = latexFormulaPixmap->scaled(QSize(width, height));
            qDebug() << latexFormulaPixmap->size();
            // Current background is dark, inverse svg to white words.
            inversePixmapFontColor(latexFormulaPixmap);
            latexLabel->setPixmap(*latexFormulaPixmap);
            latexLabel->setAlignment(Qt::AlignCenter);
        }
        else
        {
            displayMsg("Success!");
            *latexFormulaPixmap = QPixmap::fromImage(*img);
            inversePixmapFontColor(latexFormulaPixmap);
            qDebug() << img->pixelColor(0, 48);
            latexLabel->setPixmap(latexFormulaPixmap->scaled(QSize(imgSizeLimit),
                Qt::KeepAspectRatio, Qt::SmoothTransformation));
            // img->save("D:/xxx.png ", imgType.c_str(), 100);
        }

    }
    else
    {
        displayErrorMsg("No latex formula display function!");
        qDebug() << "No latex formula display";
    }
}

void View::setLatexEditor(ptr<QPlainTextEdit> iPlainTextEdit)
{
    latexEditor = iPlainTextEdit;
}
void View::setStatusBar(ptr<QStatusBar> iStatusBar)
{
    statusBar = iStatusBar;
}
void View::setTimer(ptr<QTimer> iTimer)
{
    timer = iTimer;
}
void View::setEngineSelectionInterface(ptr<EngineSelection> iEngineSelection)
{
    engineSelectionInterface = iEngineSelection;
}
void View::setCalculateInterface(ptr<Calculation> iCalculation)
{
    calculateInterface = iCalculation;
}
void View::setHelpMsgBox(ptr<QMessageBox> iMessageBox)
{
    helpMsgBox = iMessageBox;
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
    return latexString;
}
auto View::getTimer()
{
    return timer;
}
auto View::getEngineSelectionInterface()
{
    return engineSelectionInterface;
}
auto View::getCalculateInterface()
{
    return calculateInterface;
}
auto View::getHelpMsgBox()
{
    return helpMsgBox;
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
            timer->start(5000);
        }
        else
        {
            timer->stop();
        }
        return false;
    }
    else if(watched == engineSelectionInterface.get())
    {
        if (event->type() == QEvent::HideToParent)
        {
            isMathPix = engineSelectionInterface->isMathPix();
            if(isMathPix) displayMsg("Choose MathPix");
            else displayMsg("Choose Baidu");
        }
        return false;
    }
    else
    {
        return QWidget::eventFilter(watched, event);
    }
}

void View::onChangeLatexDisplay()
{
    if (latexLabel->isHidden())
    {

        qDebug() << latexString.get();
        qDebug() << latexEditor->document()->toPlainText();

        qDebug() << "Hide latexEditor";
        displayMsg("Hide latexEditor");
        latexLabel->setHidden(false);
        latexEditor->setHidden(true);

        if(latexEditor->toPlainText() != *latexString)
            onChangeLatexFormula();

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
    std::string imgDir = QFileDialog::getOpenFileName(
        NULL, "打开文件", "C:\\", "图像文件(*.jpg *.jpeg *.png *.bmp)").toStdString();

    if (loadImg4Dir && loadImg4DirB && !imgDir.empty())
    {
        imgLabel->setText("               ");
        latexLabel->setText("               ");
        imgInfo->setText(imgDir.c_str());
        imgInfo->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        qDebug() << "Load";
        if (isMathPix)
            loadImg4Dir(imgDir);
        else
            loadImg4DirB(imgDir);
        displayMsg("Load " + imgDir);
        latexEditor->setPlainText(*latexString);
        
        imgLabel->setPixmap(QPixmap(imgDir.c_str()).scaled(imgLabel->size(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation));
        
        onChangeLatexFormula();

    }
    else
    {
        displayErrorMsg("Load Aborted!");
        qDebug() << "Load Aborted!";
    }
}


void View::onClickCalculateButton()
{
	qDebug() << "打开输入变量窗口";
    calculateInterface->initQLayout(latexFormulaPixmap);
	calculateInterface->show();  
	calculateInterface->setWindowTitle("输入变量");
}

void View::onClickDownloadButton()
{
    std::string imgDir = QFileDialog::getSaveFileName(
        NULL, "保存", "C:\\", "图像文件(*.jpg *.svg *.png )").toStdString();
    if (imgDir.empty())
    {
        displayErrorMsg("Download aborted!");
        return;
    }

    const std::string imgType = imgDir.substr(imgDir.find_last_of(".") + 1);

    qDebug() << imgType.c_str();

    QSvgRenderer* svg = new QSvgRenderer;
    QImage* img = new QImage;
    int cnt = 0;
    do {
        if (cnt++ >= 2)
        {
            displayErrorMsg(imageData->constData());
            return;
        }
        renderLatexString(imgType);

        qDebug() << imageData->isEmpty();
        qDebug() << imageData->constData();

    } while (!(imgType == "svg" && svg->load(*imageData)) && !(imgType != "svg" && img->loadFromData(*imageData)));

    if (imgType == "svg")
    {
        QFile svgFile(imgDir.c_str());
        if (!svgFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            displayErrorMsg("Fail to open file: " + imgDir);
            qDebug() << QString("Fail to open file: " + QString(imgDir.c_str()));
        }
        else
        {
            QTextStream svgStream(&svgFile);
            svgStream << *imageData;
            displayMsg("Save as " + imgDir, 0);
        }
        svgFile.close();
    }
    else
    {
        img->save(imgDir.c_str(), imgType.c_str(), 100);
        displayMsg("Save as " + imgDir, 0);
    }
}
void View::installFont()
{
    // 用什么中文字还没想好
    int index = QFontDatabase::addApplicationFont("../../dependency/font/NotoSerifSC-Regular.otf");
    CHNFont = QFontDatabase::applicationFontFamilies(index).at(0);
}

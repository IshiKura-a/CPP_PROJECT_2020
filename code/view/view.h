#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPlainTextEdit>
#include <QTextDocument>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMouseEvent>
#include <QTimer>
#include <QSvgRenderer>
#include <QPainter>
#include <QFile>
#include <QEvent>
#include <QMessageBox>
#include <QDialog>
// #include "viewmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class ViewModel;

class View : public QMainWindow
{
    Q_OBJECT
private:
    // 定义类名
    using EventFunction = std::function<void()>;
    using CallbackFunction = std::function<void()>;
    using WorkFunction = std::function<void()>;
    template<typename T>
    using ptr = std::shared_ptr<T>;

public:
    View(QWidget *parent = nullptr);
    ~View();
    // 初始化布局
    void initQLayout();
    void initMenu();
    void initBody();
public:
    // 命令
    void setLoadImg4Dir(WorkFunction command)
    {
        loadImg4Dir = command;
    }
    void setRenderLatexString(WorkFunction command)
    {
        renderLatexString = command;
    }
    void setDisplayLatexFormula(WorkFunction command)
    {
        displayLatexFormula = command;
    }
    void setChangeLatexFormula(WorkFunction command)
    {
        changeLatexFormula = command;
    }
    void setDisplayHelpDocument(WorkFunction command)
    {
        displayHelpDocument = command;
    }

    // 控件设置
    void setImgLabel(ptr<QLabel> iLabel);
    void setLatexLabel(ptr<QLabel> iLabel);
    void setLatexEditor(ptr<QPlainTextEdit> iPlainTextEdit);
    void setLatexFormula(std::string iString);
    void setLatexFormula(ptr<std::string> iString);
    void setTimer(ptr<QTimer> iTimer);
    // 由ui提供
//    void setGridLayoutBody(ptr<QGridLayout> iGridLayout);
//    void setTitleMenuBar(ptr<QMenuBar> iMenuBar);

    auto getImgLabel();
    auto getLatexLabel();
    auto getLatexEditor();
    auto getLatexFormula();
    auto getGridLayoutBody();
    auto getTitleMenuBar();
    auto getTimer();

    // event callback

	void latexStringViewUpdateNotified()
	{
		// update view
	}

	void imageDataViewUpdateNotified()
	{
		// update view
	}

	void resultViewUpdateNotified()
	{
		// update view
	}

private slots:
    void onChangeLatexFormula();
    void onChangeLatexDisplay();

private:
    Ui::View *ui;

    ptr<QGridLayout> gridLayout_Body;

    ptr<QMenuBar> title_MenuBar;
    ptr<QLabel> img_Label;
    ptr<QLabel> latex_Label;
    ptr<QPlainTextEdit> latex_Editor;
    ptr<QTimer> timer;
    ptr<std::string> latex_Formula;

    // 用于动态绑定view model
	
    WorkFunction displayLatexFormula;
    WorkFunction renderLatexString;
    WorkFunction loadImg4Dir;
    WorkFunction changeLatexFormula;
    WorkFunction displayHelpDocument;
    WorkFunction changeLatexDisplay;


    // img_Label和latex_Label事件过滤器
    bool eventFilter(QObject *watched, QEvent *event);
};
#endif // VIEW_H

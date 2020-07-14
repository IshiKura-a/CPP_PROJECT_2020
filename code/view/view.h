#pragma once
#include <memory>

#include "../common/def.h"

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

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class ViewModel;

class View : public QMainWindow
{
	Q_OBJECT

public:
	View(QWidget* parent = nullptr);
	~View();
	// 初始化布局
	void initQLayout();
	void initMenu();
	void initBody();

	// 命令
	void setLoadImg4Dir(WorkFunction command)
	{
		loadImg4Dir = command;
	}
	void setRenderLatexString(WorkFunctionNoArg command)
	{
		renderLatexString = command;
	}
	void setDisplayLatexFormula(WorkFunctionNoArg command)
	{
		displayLatexFormula = command;
	}
	void setChangeLatexFormula(WorkFunctionNoArg command)
	{
		changeLatexFormula = command;
	}
	void setDisplayHelpDocument(WorkFunctionNoArg command)
	{
		displayHelpDocument = command;
	}

	/******************** function entry ********************/

	void loadImageFromDir(std::string file_path)
	{
		loadImg4Dir(file_path);
	}

	/******************** data-getter setter and data-setter setter ********************/

	void setLatexStringGetter(Getter<ptr<const std::string>> getter)
	{
		latexStringGetter = getter;
	}
	void setLatexStringSetter(Setter<std::string> setter)
	{
		latexStringSetter = setter;
	}

	/******************** data getter and setter ********************/
	// 有用吗, 没用就删了

	auto getLatexString()
	{
		return latexStringGetter();
	}
	void setLatexString(const std::string& str)
	{
		latexStringSetter(str);
	}
	
	// 控件设置
	void setImgLabel(ptr<QLabel> iLabel);
	void setLatexLabel(ptr<QLabel> iLabel);
	void setLatexEditor(ptr<QPlainTextEdit> iPlainTextEdit);
	// void setLatexFormula(std::string iString);
	void setLatexFormula(ptr<const std::string> iString);
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
	
	/******************** callback function ********************/

	void latexStringViewUpdateNotified()
	{
		// TODO:
		// update view
		latex_Formula = latexStringGetter();
	}

	void imageDataViewUpdateNotified()
	{
		// TODO:
		// update view
	}

	void varValPairsUpdateNotified()
	{
		// TODO:
		// update view
	}

	void resultViewUpdateNotified()
	{
		// TODO:
		// update view
	}

private slots:
	void onChangeLatexFormula();
	void onChangeLatexDisplay();

private:
	Ui::View* ui;

	ptr<QGridLayout> gridLayout_Body;

	ptr<QMenuBar> title_MenuBar;
	ptr<QLabel> img_Label;
	ptr<QLabel> latex_Label;
	ptr<QPlainTextEdit> latex_Editor;
	ptr<QTimer> timer;

	// view model数据
	// TODO:
	// 补充其他数据的指针
	// 注意添加getter and setter

	ptr<const std::string> latex_Formula;

	Getter<ptr<const std::string>> latexStringGetter;
	Setter<std::string> latexStringSetter;

	// 用于动态绑定view model

	WorkFunctionNoArg displayLatexFormula;
	WorkFunctionNoArg renderLatexString;
	WorkFunction loadImg4Dir;
	WorkFunctionNoArg changeLatexFormula;
	WorkFunctionNoArg displayHelpDocument;
	WorkFunctionNoArg changeLatexDisplay;


	// img_Label和latex_Label事件过滤器
	bool eventFilter(QObject* watched, QEvent* event);
};

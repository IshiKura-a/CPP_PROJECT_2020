#pragma once
#include <memory>

#include "../common/def.h"
#include "engineselection.h"
#include "stylesheet.h"

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
#include <QStatusBar>
#include <QRadioButton>
#include <QFileDialog>
#include <QDesktopServices>
#include <QFontDatabase>
#include <QBitmap>
#include "calculation.h"

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
	void initCmdInterface();
	void installFont();

	// 命令
	void setLoadImg4Dir(const WorkFunction& command)
	{
		loadImg4Dir = command;
	}
	void setLoadImg4DirB(const WorkFunction& command)
	{
		loadImg4DirB = command;
	}
	void setRenderLatexString(const WorkFunction& command)
	{
		renderLatexString = command;
	}

	// void setDisplayLatexFormula(const WorkFunctionNoArg& command)
	// {
	//	displayLatexFormula = command;
  	//}
	void setDisplayHelpDocument(const WorkFunctionWithRetVal& command)
	{
		displayHelpDocument = command;
	}
	void setPrettifyLatexFormula(WorkFunctionNoArg command)
	{
		prettifyLatexFormula = command;
	}
	
	void setCalculateLatexFormula(WorkFunctionNoArg command)
	{
		calculateInterface->setCalculateLatexFormula(command);
	}
	
	/******************** function entry ********************/

	void loadImageFromDir(const std::string& file_path)
	{
		loadImg4Dir(file_path);
	}

	/******************** data-getter setter and data-setter setter ********************/

	void setLatexStringGetter(const Getter<ptr<const QString>>& getter)
	{
		latexStringGetter = getter;
	}
	void setLatexStringSetter(const Setter<QString>& setter)
	{
		latexStringSetter = setter;
	}
	void setImageDataGetter(const Getter<ptr<const QByteArray>>& getter)
	{
		imageDataGetter = getter;
	}
	
	void setVarValPairsGetter(const Getter<ptr<const QVector<VarValPair>>>& getter)
	{
		calculateInterface->setVarValPairsGetter(getter);
		// varValPairsGetter = getter;
	}
	void setVarValPairsSetter(const Setter<const QVector<VarValPair>>& setter)
	{
		calculateInterface->setVarValPairsSetter(setter);
		// varValPairsSetter = setter;
	}
	void setResultGetter(const Getter<ptr<const QString>>& getter)
	{
		calculateInterface->setResultGetter(getter);
		// resultGetter = getter;
	}
	
	/******************** data getter and setter ********************/

	auto getLatexString() const
	{
		return latexStringGetter();
	}
	void setLatexString(const QString& str)
	{
		latexStringSetter(str);
		latexString = latexStringGetter();
	}

	// 控件设置
	
	void setLatexEditor(ptr<QPlainTextEdit> iPlainTextEdit);
	void setStatusBar(ptr<QStatusBar> iStatusBar);
	void setTimer(ptr<QTimer> iTimer);
	void setEngineSelectionInterface(ptr<EngineSelection> iEngineSelection);
	void setCalculateInterface(ptr<Calculation> iViewCalculate);
	void setHelpMsgBox(ptr<QMessageBox> iMessageBox);

	auto getImgLabel();
	auto getLatexLabel();
	auto getLatexEditor();
	auto getLatexFormula();
	auto getGridLayoutBody();
	auto getTitleMenuBar();
	auto getTimer();
	auto getStatusBar();
	auto getEngineSelectionInterface();
	auto getCalculateInterface();
	auto getHelpMsgBox();
	
	/******************** callback function ********************/

	void latexStringViewUpdateNotified()
	{
		latexString = latexStringGetter();
	}

	void imageDataViewUpdateNotified()
	{
		imageData = imageDataGetter();
	}
	
	void varValPairsUpdateNotified()
	{
		calculateInterface->varValPairsUpdateNotified();
		// varValPairs = varValPairsGetter();
	}

	void resultViewUpdateNotified()
	{
		calculateInterface->resultViewUpdateNotified();
		// result = resultGetter();
	}
	
private slots:
	void onChangeLatexFormula();
	void onChangeLatexDisplay();
	void onClickLoadButton();
	void onClickCalculateButton();
	void onClickDownloadButton();

private:
	Ui::View* ui;

	ptr<QGridLayout> gridLayoutBody;

	ptr<QMenuBar> titleMenuBar;
	ptr<QLabel> imgLabel;
	ptr<QLabel> latexLabel;
	ptr<QLabel> globalFunctionalZoneLabel;
	ptr<QLabel> formulaDealerZoneLabel;
	ptr<QPlainTextEdit> latexEditor;
	ptr<QTimer> timer;
	ptr<QStatusBar> statusBar;
	ptr<QPushButton> loadButton;
	ptr<QPushButton> editButton;
	ptr<QPushButton> downloadButton;
	ptr<QPushButton> resetButton;
	ptr<QTextEdit> imgInfo;
	ptr<QPushButton> calculateButton;
	ptr<QPushButton> applyButton;
	ptr<QPushButton> prettifyButton;
	ptr<EngineSelection> engineSelectionInterface;
	ptr<Calculation> calculateInterface;
	ptr<QMessageBox> helpMsgBox;

	// View层数据
	ptr<QPixmap> latexFormulaPixmap;

	// view model数据对象指针

	ptr<const QString> latexString;
	ptr<const QByteArray> imageData;

	/*
	ptr<const QVector<VarValPair>> varValPairs;
	ptr<const QString> result;
	*/

	Getter<ptr<const QString>> latexStringGetter;
	Setter<QString> latexStringSetter;
	Getter<ptr<const QByteArray>> imageDataGetter;

	/*
	Getter<ptr<const QVector<VarValPair>>> varValPairsGetter;
	Setter<const QVector<VarValPair>> varValPairsSetter;
	Getter<ptr<const QString>> resultGetter;
	*/

	// 用于动态绑定view model
	// 有参数的函数定义为WorkFunction，无参数的函数定义为WorkFunctionNoArg
	// WorkFunctionNoArg displayLatexFormula;
	WorkFunction renderLatexString;
	WorkFunction loadImg4Dir;
	WorkFunction loadImg4DirB;
	WorkFunctionWithRetVal displayHelpDocument;
	// WorkFunctionNoArg applyLatexFormulaChanges;
	WorkFunctionNoArg prettifyLatexFormula;
	// WorkFunctionNoArg calculateLatexFormula;  

	// 选择识别引擎
	bool isMathPix = true;
	QSize screenSize;
	QSize imgSizeLimit;


	// imgLabel和latexLabel事件过滤器
	bool eventFilter(QObject* watched, QEvent* event);
	// 底部消息提示函数
	// @param:
	// msg: 提示消息
	// duration: 提示时间，缺省为4000ms
	void displayMsg(std::string msg, int duration = 4000);
	// @param:
	// msg: 提示错误消息，消息常驻
	void displayErrorMsg(std::string errorMsg);
	
};

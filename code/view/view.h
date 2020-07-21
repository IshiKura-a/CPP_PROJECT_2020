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
#include "viewCalculate.h"
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
	viewCalculate *new_mainw;

	// 命令
	void setLoadImg4Dir(const WorkFunction& command)
	{
		loadImg4Dir = command;
	}
	void setRenderLatexString(const WorkFunction& command)
	{
		renderLatexString = command;
	}
	//void setDisplayLatexFormula(const WorkFunctionNoArg& command)
	//{
		//displayLatexFormula = command;
	//}
	void setDisplayHelpDocument(const WorkFunctionNoArg& command)
	{
		displayHelpDocument = command;
	}
	void setPrettifyLatexFormula(WorkFunctionNoArg command)
	{
		prettifyLatexFormula = command;
	}
	void setCalculateLatexFormula(WorkFunctionNoArg command)
	{
		calculateLatexFormula = command;
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
		varValPairsGetter = getter;
	}
	void setVarValPairsSetter(const Setter<const QVector<VarValPair>>& setter)
	{
		varValPairsSetter = setter;
	}
	void setResultGetter(const Getter<ptr<const QString>>& getter)
	{
		resultGetter = getter;
	}

	/******************** data getter and setter ********************/
	// 有用吗, 没用就删了

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

	auto getImgLabel();
	auto getLatexLabel();
	auto getLatexEditor();
	auto getLatexFormula();
	auto getGridLayoutBody();
	auto getTitleMenuBar();
	auto getTimer();
	auto getStatusBar();
	auto getEngineSelectionInterface();
	
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
		varValPairs = varValPairsGetter();
	}

	void resultViewUpdateNotified()
	{
		result = resultGetter();
	}

private slots:
	void onChangeLatexFormula();
	void onChangeLatexDisplay();
	void onClickLoadButton();
	void onClickCalculateButton();

private:
	Ui::View* ui;

	ptr<QGridLayout> gridLayoutBody;

	ptr<QMenuBar> titleMenuBar;
	ptr<QLabel> imgLabel;
	ptr<QLabel> latexLabel;
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

	// view model数据对象指针

	ptr<const QString> latexString;
	ptr<const QByteArray> imageData;
	ptr<const QVector<VarValPair>> varValPairs;
	ptr<const QString> result;

	Getter<ptr<const QString>> latexStringGetter;
	Setter<QString> latexStringSetter;
	Getter<ptr<const QByteArray>> imageDataGetter;
	Getter<ptr<const QVector<VarValPair>>> varValPairsGetter;
	Setter<const QVector<VarValPair>> varValPairsSetter;
	Getter<ptr<const QString>> resultGetter;

	// 用于动态绑定view model
	//有参数的函数定义为WorkFunction，无参数的函数定义为WorkFunctionNoArg
	//WorkFunctionNoArg displayLatexFormula;
	WorkFunction renderLatexString;
	WorkFunction loadImg4Dir;
	WorkFunctionNoArg displayHelpDocument;
	// WorkFunctionNoArg applyLatexFormulaChanges;
	WorkFunctionNoArg prettifyLatexFormula;
	WorkFunctionNoArg calculateLatexFormula;  

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
	
	// Font
	QFont textNormal = QFont("Courier New", 14, QFont::Normal, false);
	QFont textBold = QFont("Courier New", 14, QFont::Bold, false);
	QFont titleBold = QFont("Courier New", 22, QFont::Bold, false);
	QFont menuNormal = QFont("微软雅黑", 10, QFont::Normal, false);
	QFont msgNormal = QFont("Courier New", 10, QFont::Normal, false);

	// StyleSheet
	const QString whiteBackground = "background: white;";
	const QString lightBlueBackground = "background: #7BD9D2; ";
	const QString lightDarkBackground = "background: #2E323A;";

	const QString whiteWords = "color: white;";
	const QString redWords = "color: #FF5555;";
	const QString blackWords = "color: black;";

	const QString blackBorder2Px = "border: 2px solid black;";
	const QString noBottomBorder = "border-bottom: 0px;";

	const QString textFontSize = "font-size: 14px";

	// @param:
	// width: default下的width
	// height: default下的height
	// @return
	// 调整后的size
	inline QSize getAdaptedSize(int width, int height)
	{
		// sysWidth: resolution_width / expanding rate
		// sysHeight: resolution_height / expanding rate
		// The dafault size of screen is 1920*1080 125%
		// In this case, the size of the software is 960*600.
		// In case of different solutionn, change the width and height in proportion.
		// Windows.h MUST be included!!!
		int sysWidth = ::GetSystemMetrics(SM_CXSCREEN);
		int sysHeight = ::GetSystemMetrics(SM_CYSCREEN);
		int adaptedWidth = (width * sysWidth) / 1536;
		int adaptedHeight = (height * sysHeight) / 864;
		return QSize(adaptedWidth, adaptedHeight);
	}
	inline QSize getAdaptedSize(QSize size)
	{
		return getAdaptedSize(size.width(), size.height());
	}
};

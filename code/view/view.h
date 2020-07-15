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
#include <QStatusBar>
#include <QRadioButton>

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
	void setLoadImg4Dir(const WorkFunction& command)
	{
		loadImg4Dir = command;
	}
	void setRenderLatexString(const WorkFunction& command)
	{
		renderLatexString = command;
	}
	void setDisplayLatexFormula(const WorkFunctionNoArg& command)
	{
		displayLatexFormula = command;
	}
	void setChangeLatexFormula(const WorkFunctionNoArg& command)
	{
		changeLatexFormula = command;
	}
	void setDisplayHelpDocument(const WorkFunctionNoArg& command)
	{
		displayHelpDocument = command;
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
	}

	// 控件设置
	void setImgLabel(ptr<QLabel> iLabel);
	void setLatexLabel(ptr<QLabel> iLabel);
	void setLatexEditor(ptr<QPlainTextEdit> iPlainTextEdit);
	// void setLatexFormula(std::string iString);
	void setLatexFormula(ptr<const QString> iString);
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
		latexFormula = latexStringGetter();
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
	ptr<QRadioButton> baiduButton;
	ptr<QRadioButton> mathpixButton;
	ptr<QPlainTextEdit> imgInfo;
	ptr<QPushButton> calculateButton;

	// view model数据对象指针

	ptr<const QString> latexFormula;
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

	WorkFunctionNoArg displayLatexFormula;
	WorkFunction renderLatexString;
	WorkFunction loadImg4Dir;
	WorkFunctionNoArg changeLatexFormula;
	WorkFunctionNoArg displayHelpDocument;
	WorkFunctionNoArg changeLatexDisplay;


	// imgLabel和latexLabel事件过滤器
	bool eventFilter(QObject* watched, QEvent* event);
	// 底部消息提示函数
	void displayMsg(std::string msg, int duration = 0);
	void displayErrorMsg(std::string errorMsg);

	// Font
	const QFont textNormal = QFont("Courier New", 14, QFont::Normal, false);
	const QFont textBold = QFont("Courier New", 14, QFont::Bold, false);
	const QFont titleBold = QFont("Courier New", 22, QFont::Bold, false);
	const QFont menuNormal = QFont("微软雅黑", 10, QFont::Normal, false);
	const QFont msgNormal = QFont("Courier New", 10, QFont::Normal, false);

	// StyleSheet
	const QString whiteBackground = "background: white;";
	const QString lightBlueBackground = "background: #7BD9D2; ";
	const QString lightDarkBackground = "background: #2E323A;";

	const QString whiteWords = "color: white;";
	const QString redWords = "color: #FF5555;";
	const QString blackWords = "color: black;";

	const QString blackBorder2Px = "border: 2px solid black;";
	const QString noBottomBorder = "border-bottom: 0px;";

};

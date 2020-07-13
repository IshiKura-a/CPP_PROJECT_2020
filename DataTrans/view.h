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
    explicit View(QWidget *parent = nullptr);
    ~View();
    // 初始化布局
    void initQLayout();
    void initMenu();
    void initBody();
public:
    // 绑定
/*    void bindViewModel(ptr<ViewModel> iViewModel)
    {
        // 绑定命令
        this->setRenderLatexString(iViewModel->getRenderLatexString());
        this->setDisplayLatexFormula(iViewModel->getGetFormulaResult());
        this->setLoadImg4Dir(iViewModel->getLoadImg4Dir());
        this->setChangeLatexFormula(iViewModel->getChangeLatexFormula());
        this->setDisplayHelpDocument(iViewModel->getDisplayHelpDocument());

        // 绑定数据
        this->setLatexFormula(iViewModel->getLatexString());
        // 绑定通知
        this->setLatexStringViewUpdateNotifier(iViewModel->getLatexStringViewUpdateNotifier());
    }*/
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
    void setLatexFormula(ptr<std::string> iString);
    // 由ui提供
//    void setGridLayoutBody(ptr<QGridLayout> iGridLayout);
//    void setTitleMenuBar(ptr<QMenuBar> iMenuBar);

    auto getImgLabel();
    auto getLatexLabel();
    auto getLatexEditor();
    auto getLatexFormula();
    auto getGridLayoutBody();
    auto getTitleMenuBar();

    // 通知
    void setLatexStringViewUpdateNotifier(EventFunction notifier)
    {
        latexStringViewUpdateNotifier = notifier;
    }
    auto getLatexStringViewUpdateNotifier()
    {
        return latexStringViewUpdateNotifier;
    }

private slots:
    void onChangeLatexFormula();

private:
    Ui::View *ui;

    ptr<QGridLayout> gridLayout_Body;

    ptr<QMenuBar> title_MenuBar;
    ptr<QLabel> img_Label;
    ptr<QLabel> latex_Label;
    ptr<QPlainTextEdit> latex_Editor;
    ptr<std::string> latex_Formula;

    WorkFunction displayLatexFormula;
    WorkFunction renderLatexString;
    WorkFunction loadImg4Dir;
    WorkFunction changeLatexFormula;
    WorkFunction displayHelpDocument;

    EventFunction latexStringViewUpdateNotifier;
};
#endif // VIEW_H

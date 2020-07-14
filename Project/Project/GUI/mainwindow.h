#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QTextEdit>
#include <QLineEdit>
#include "set_ui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    set_ui *new_mainw;
private slots:
    void displayPic4Url(QNetworkReply *reply);
    void changeLatexLayout();
    void on_pushButton_clicked(); //添加槽函数,并且把槽函数和pushButton的信号函数关联起来
private:
    void initQVLayout();
    void initMenu();
    void createInput();
    void initBody();
    void latexDisplay();
    bool eventFilter(QObject *obj, QEvent *event);
private:
    Ui::MainWindow *ui;

    QHBoxLayout* hLayout_Menu;
    QGridLayout* gridLayout_Body;

    QMenuBar* title_MenuBar;
    QLabel* img_Label;
    QLabel* latex_Label;
    QPlainTextEdit* latex_Editor;
    QNetworkAccessManager* net_Manager;
    QTimer* timer;
    QTextEdit *TextEdit1, *TextEdit2;
};
#endif // MAINWINDOW_H

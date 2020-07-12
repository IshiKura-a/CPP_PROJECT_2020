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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void displayPic4Url(QNetworkReply *reply);
    void changeLatexLayout();
private:
    void initQVLayout();
    void initMenu();
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
};
#endif // MAINWINDOW_H

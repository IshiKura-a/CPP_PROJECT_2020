#ifndef SET_UI_H
#define SET_UI_H

#include <QMainWindow>

namespace Ui {
class set_ui;
}

class set_ui : public QMainWindow
{
    Q_OBJECT

public:
    explicit set_ui(QWidget *parent = 0);
    ~set_ui();

private:
    Ui::set_ui *ui;
    void initQVLayout();
    void on_lineEdit_returnPressed();
};

#endif // SET_UI_H

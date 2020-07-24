#pragma once

#include <QWidget>
#include <QRadioButton>
#include <Windows.h>
#include "ui_engineselection.h"
#include "stylesheet.h"
#include "../common/def.h"

class EngineSelection : public QWidget
{
	Q_OBJECT

public:
	EngineSelection(QWidget *parent = Q_NULLPTR) : ui(new Ui::EngineSelection)
	{ 
		ui->setupUi(this);
		baiduRadioButton = ptr<QRadioButton>(ui->baiduRadioButton);
		mathPixRadioButton = ptr<QRadioButton>(ui->mathPixRadioButton);
	}
	~EngineSelection(){}
	void initQLayout()
	{
		setWindowTitle("Select Engine");
		setFixedSize(getAdaptedSize(250, 80));

		setStyleSheet(background4Img);
		setAttribute(Qt::WA_StyledBackground, true);

		baiduRadioButton->setStyleSheet(whiteWords);
		baiduRadioButton->setFont(msgNormal);
		mathPixRadioButton->setStyleSheet(whiteWords);
		mathPixRadioButton->setFont(msgNormal);
	}
	bool isMathPix()
	{
		return mathPixRadioButton->isChecked();
	}
	void setMathPix(bool iBool)
	{
		mathPixRadioButton->setChecked(iBool);
		baiduRadioButton->setChecked(!iBool);
	}
private:
	Ui::EngineSelection* ui;
	ptr<QRadioButton> baiduRadioButton;
	ptr<QRadioButton> mathPixRadioButton;
};

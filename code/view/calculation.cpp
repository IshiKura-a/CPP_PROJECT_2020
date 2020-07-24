#include "calculation.h"

Calculation::Calculation(QWidget *parent)
	: QWidget(parent), ui(new Ui::Calculation)
{
	ui->setupUi(this);

    varLineEdit = ptr<QLineEdit>(ui->varLineEdit);
    valLineEdit = ptr<QLineEdit>(ui->valLineEdit);
    answerLineEdit = ptr<QLineEdit>(ui->answerLineEdit);
    precisionSpinBox = ptr<QSpinBox>(ui->precisionSpinBox);
    addButton = ptr<QPushButton>(ui->addButton);
    computionButton = ptr<QPushButton>(ui->computionButton);
    deleteLastButton = ptr<QPushButton>(ui->deleteLastButton);
    titleLabel = ptr<QLabel>(ui->titleLabel);
    varLabel = ptr<QLabel>(ui->varLabel);
    valLabel = ptr<QLabel>(ui->valLabel);
    answerLabel = ptr<QLabel>(ui->answerLabel);
    imgLabel = ptr<QLabel>(ui->imgLabel);
    bitLabel = ptr<QLabel>(ui->bitLabel);
    precisionLabel = ptr<QLabel>(ui->precisionLabel);
    varValSheetTable = ptr<QTableWidget>(ui->varValSheetTable);
    gridLayout = ptr<QGridLayout>(ui->gridLayout);
}

void Calculation::initQLayout(ptr<QPixmap> latexFormulaPixmap)
{
    static int initCount = 0;

    setStyleSheet(background4Img);
    // must include this to make the whole widget
    // painted by the picture.
    setAttribute(Qt::WA_StyledBackground, true);
    
    setMinimumSize(getAdaptedSize(960,600));
    imgLabel->setMargin(0);
    answerLineEdit->setText("");
    setLatexFormulaImage(latexFormulaPixmap);

    // style setting
    imgLabel->setStyleSheet(transparentBackground + blackBorder2Px);
    titleLabel->setStyleSheet(transparentBackground + whiteWords);
    varLabel->setStyleSheet(transparentBackground + whiteWords);
    valLabel->setStyleSheet(transparentBackground + whiteWords);
    answerLabel->setStyleSheet(transparentBackground + whiteWords);
    precisionLabel->setStyleSheet(transparentBackground + whiteWords);
    bitLabel->setStyleSheet(transparentBackground + whiteWords);

    varLineEdit->setStyleSheet(whiteBackground);
    valLineEdit->setStyleSheet(whiteBackground);
    answerLineEdit->setStyleSheet(whiteBackground);
    addButton->setStyleSheet(whiteBackground);
    deleteLastButton->setStyleSheet(whiteBackground);
    computionButton->setStyleSheet(whiteBackground);

    varValSheetTable->setStyleSheet(whiteWords);
    // must include this to ensure the table is transparent
    // rather than load the background of centeral widget only.
    varValSheetTable->setAttribute(Qt::WA_TranslucentBackground);
    varValSheetTable->horizontalHeader()->setStyleSheet(blackWords);
    varValSheetTable->verticalHeader()->setHidden(true);
    varValSheetTable->verticalScrollBar()->setStyleSheet(lightDarkBackground);

    titleLabel->setFont(titleBoldCHN);
    varLabel->setFont(labelTextNormalCHN);
    valLabel->setFont(labelTextNormalCHN);
    answerLabel->setFont(labelTextNormalCHN);
    precisionLabel->setFont(labelTextNormalCHN);
    bitLabel->setFont(labelTextNormalCHN);

    varLineEdit->setFont(labelTextNormal);
    valLineEdit->setFont(labelTextNormal);
    answerLineEdit->setFont(labelTextNormal);
    precisionSpinBox->setFont(labelTextNormal);

    addButton->setFont(labelTextNormal);
    deleteLastButton->setFont(labelTextNormal);
    computionButton->setFont(labelTextNormal);

    varValSheetTable->setFont(labelTextNormal);
    varValSheetTable->horizontalHeader()->setFont(labelTextBold);

    tableRowCount = 0;
    varValSheetTable->setRowCount(0);
    varValSheetTable->setColumnCount(2);
    varValSheetTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList header;
    header << "Var" << "Val";
    
    varValSheetTable->setHorizontalHeaderLabels(header);

    answerLineEdit->setReadOnly(true);

    // varValSheetTable->setItem(0, 0, new QTableWidgetItem("\\epsilon"));
    // varValSheetTable->setItem(0, 1, new QTableWidgetItem("3"));

    // To avoid reconnect, only initCount == 0, connect
    if (!initCount)
    {
        connect(addButton.get(), &QPushButton::clicked, [=]() {
            QTableWidgetItem* newVarItem = new QTableWidgetItem(varLineEdit->text());
            QTableWidgetItem* newValItem = new QTableWidgetItem(valLineEdit->text());

            varValSheetTable->setRowCount(tableRowCount + 1);
            varValSheetTable->setItem(tableRowCount, 0, newVarItem);
            varValSheetTable->setItem(tableRowCount, 1, newValItem);
            tableRowCount++;

            varLineEdit->setText("");
            valLineEdit->setText("");
            });

        // To delete, decrease tableRowCount only.
        connect(deleteLastButton.get(), &QPushButton::clicked, [=]() {
            if (tableRowCount)
                varValSheetTable->setRowCount(--tableRowCount);
            });

        // To compute, generate a QVector temporarily.
        connect(computionButton.get(), &QPushButton::clicked, [=]() {
            QVector<VarValPair>* varValData = new QVector<VarValPair>;

            int i;
            
            for (i = 0; i < tableRowCount; i++)
            {
                VarValPair varValItem = std::make_pair(
                    varValSheetTable->item(i, 0)->text().toStdString(),
                    varValSheetTable->item(i, 1)->text().toStdString());

                varValData->append(varValItem);
            }
            qDebug() << varValData->size();

            if (calculateLatexFormula)
            {
                qDebug() << "Calculate Latex Formula";
                
                
                varValPairsSetter(*varValData);
                calculateLatexFormula();
                result = resultGetter();
                // answerLineEdit->setText(*result);
                
                // const QString textString = "123";
                int precision = precisionSpinBox->value();
               
                // QString utf8String = QString::fromUtf8(result->toStdString().c_str());

                int i;
                int indexOfApproxEq = -1;
                for (i = 0; i < result->size(); i++)
                {
                    if ((unsigned short)(result->at(i).unicode()) == 8776)
                    {
                        indexOfApproxEq = i;
                        break;
                    }
                }
                // std::string displayedAnsString = textString.toStdString();

                std::string approxAnsString;
                std::string analyticAnsString;
                if (indexOfApproxEq == -1)
                {
                    analyticAnsString = "";
                    approxAnsString = result->toStdString();
                }
                else
                {
                    analyticAnsString = result->toStdString().substr(0, indexOfApproxEq + 3);
                    approxAnsString = result->toStdString().substr(indexOfApproxEq + 3);
                }
                
                
                // test if ans is valid
                if (true)
                {
                    if (precision >= 0)
                    {
                        // use stringstream to control precision.
                        std::stringstream ss;
                        double ans;
                        ss << approxAnsString;
                        ss >> ans;

                        ss.clear();
                        ss.setf(std::ios::showpoint);
                        ss.precision(precision);
                        ss.setf(std::ios::fixed);
                        ss << ans;
                        ss >> approxAnsString;
                        if (approxAnsString.back() == '.')
                            approxAnsString.pop_back();
                    }
                }
                
                answerLineEdit->setText(QString(analyticAnsString.c_str()) + QString(approxAnsString.c_str()));
                // calculateLatexFormula(varValData);
            }
            else
            {
                qDebug() << "No calculation function found!";
            }

            });
    }
    initCount++;

}

void Calculation::setLatexFormulaImage(ptr<QPixmap> latexFormulaPixmap)
{
    
    int width, height;

    // Leave some margin for the pic.
    QSize imgSizeLimit = QSize((int)(imgLabel->size().width() * 0.9),
        (int)(imgLabel->size().height() * 0.9));

    if (latexFormulaPixmap)
    {
        imgLabel->setPixmap(latexFormulaPixmap->scaled(QSize(imgSizeLimit),
            Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imgLabel->setAlignment(Qt::AlignCenter);
    }
}
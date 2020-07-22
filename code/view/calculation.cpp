#include <QSvgRenderer>
#include <QPainter>
#include <QDebug>
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
}

void Calculation::initQLayout(ptr<const QByteArray> imageData)
{
    static int initCount = 0;
    imgLabel->setMargin(0);
    setLatexFormulaImage(imageData);

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
            QVector<RawVarValPair>* varValData = new QVector<RawVarValPair>;

            int i;
            
            for (i = 0; i < tableRowCount; i++)
            {
                RawVarValPair varValItem = std::make_pair(
                    varValSheetTable->item(i, 0)->text().toStdString(),
                    varValSheetTable->item(i, 1)->text().toStdString());

                varValData->append(varValItem);
            }
            qDebug() << varValData->size();

            if (calculateLatexFormula)
            {
                qDebug() << "Calculate Latex Formula";
                calculateLatexFormula(varValData);
            }
            else
            {
                qDebug() << "No calculation function found!";
            }

            });
    }
    initCount++;

}

void Calculation::setLatexFormulaImage(ptr<const QByteArray> imageData)
{
    QSvgRenderer* svg = new QSvgRenderer;
    QImage* img = new QImage;
    int width, height;

    // Leave some margin for the pic.
    QSize imgSizeLimit = QSize((int)(imgLabel->size().width() * 0.9),
        (int)(imgLabel->size().height() * 0.9));

    // If imageData is svg-format, the first if will success.
    // If imageData is jpg/png-format, the second if will be true.
    // If it's empty, paint it white(to relarge the label).
    if (svg->load(*imageData))
    {
        qDebug() << svg->defaultSize();

        width = svg->defaultSize().width();
        height = svg->defaultSize().height();

        if ((height * imgSizeLimit.width() / width) <= imgSizeLimit.height())
        {
            height = (height * imgSizeLimit.width() / width);
            width = imgSizeLimit.width();
        }
        else
        {
            width = (width * imgSizeLimit.height()) / height;
            height = imgSizeLimit.height();
        }


        QPixmap* pixmap = new QPixmap(QSize(width, height));
        //img->loadFromData(img_bytes);
        pixmap->fill(Qt::white);
        QPainter painter(pixmap);
        svg->render(&painter);

        imgLabel->setPixmap(*pixmap);
        imgLabel->setAlignment(Qt::AlignCenter);
    }
    else if (img->loadFromData(*imageData))
    {
        imgLabel->setPixmap(QPixmap::fromImage(*img, Qt::AutoColor).scaled(QSize(imgSizeLimit),
            Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imgLabel->setAlignment(Qt::AlignCenter);
    }
    else
    {
        QPixmap* tmpPixmap = new QPixmap(631,190);
        tmpPixmap->fill(Qt::white);
        imgLabel->setPixmap(*tmpPixmap);
        qDebug() << imgLabel->size();
    }
}
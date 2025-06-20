#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextTable>
#include <QTextCursor>
#include <QComboBox>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // tableWidget = new QTableWidget();
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::saveTableToPdf);

    itemsCost["Brand Consultation"] = 100;
    itemsCost["Logo Design"] = 100;
    itemsCost["Website Design"] = 100;
    itemsCost["Social media templates"] = 100;
    itemsCost["Brand photography"] = 100;
    itemsCost["Brand guide"] = 100;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::saveTableToPdf()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Save as PDF", "", ".*pdf");
    qDebug()<<filepath;
    if(filepath.isEmpty())
        return;
    if(!filepath.endsWith(".pdf"))
        filepath += ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filepath);

    QTextDocument doc;
    QTextCursor cursor(&doc);

    QTextCharFormat formatBold;
    formatBold.setFontWeight(QFont::Bold);
    QTextCharFormat formatNormal;
    formatNormal.setFontWeight(200);

    QTextBlockFormat formatLeft;
    formatLeft.setAlignment(Qt::AlignLeft);

    QTextBlockFormat formatRight;
    formatRight.setAlignment(Qt::AlignRight);

    // Set centered block format
    QTextBlockFormat formatCenter;
    formatCenter.setAlignment(Qt::AlignCenter);

    cursor.setBlockFormat(formatLeft);
    // Insert the logo image
    QTextImageFormat imageFormat;
    imageFormat.setName(":/logo/two.png"); // Use a valid path to your image
    imageFormat.setWidth(25);  // Set size as needed
    imageFormat.setHeight(25);
    cursor.insertImage(imageFormat);

    // Insert some spacing between image and text
    cursor.insertText("    ");  // Two spaces

    // Insert the company name text
    QTextCharFormat companyNameFormat;
    companyNameFormat.setFontPointSize(22);
    companyNameFormat.setFontWeight(QFont::Bold);
    cursor.insertText("ABC Pvt Ltd", companyNameFormat);

    cursor.insertBlock();
    cursor.insertBlock();

    QTextTableFormat tableMain;
    tableMain.setBorder(1);
    tableMain.setCellPadding(10);
    tableMain.setCellSpacing(2);
    tableMain.setAlignment(Qt::AlignCenter);
    tableMain.setWidth(QTextLength(QTextLength::PercentageLength, 100));

    QTextTable *infoTable = cursor.insertTable(2, 2, tableMain);

    QTextCursor issueCursor = infoTable->cellAt(0, 0).firstCursorPosition();
    issueCursor.insertText("ISSUE TO : \n", formatBold);
    issueCursor.insertText(ui->issuedToLineEdit->text()+"\n", formatNormal);

    QTextCursor payCursor = infoTable->cellAt(1, 0).firstCursorPosition();
    payCursor.insertText("PAY TO : \n", formatBold);
    payCursor.insertText(ui->payToLineEdit->text()+"\n", formatNormal);
    payCursor.insertText(ui->accNameLineEdit->text() + "\n", formatNormal);
    payCursor.insertText(ui->accNoLineEdit->text() + "\n", formatNormal);

    QTextCursor invoiceCursor = infoTable->cellAt(0, 1).firstCursorPosition();
    invoiceCursor.insertText("INVOICE NO. :  ", formatBold);
    invoiceCursor.insertText(ui->invoiceNumberLineEdit->text() + "\n", formatNormal);
    invoiceCursor.insertText("DATE             :  ",formatBold);
    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    invoiceCursor.insertText(date, formatNormal);
    invoiceCursor.insertText("\nDUE DATE       :  ",formatBold);
    invoiceCursor.insertText(ui->dueDateLineEdit->text(), formatNormal);

    cursor.movePosition(QTextCursor::End);
    cursor.insertHtml("<hr style='height:2px;border-width:0;color:black;background-color:gray'>");

    QTextTableFormat tableList;
    tableList.setBorder(1);
    tableList.setCellPadding(2);
    tableList.setAlignment(Qt::AlignCenter);
    tableList.setWidth(QTextLength(QTextLength::PercentageLength, 100));

    QTextTable *textTable = cursor.insertTable(
        1,
        ui->tableWidget->columnCount(),
        tableList);

    // Set header
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col)
    {
        QTextCursor cellCursor = textTable->cellAt(0, col).firstCursorPosition();
        cellCursor.insertText(ui->tableWidget->horizontalHeaderItem(col)->text(), formatBold);

    }
    cursor.movePosition(QTextCursor::End);
    cursor.insertHtml("<hr style='height:2px;border:0;background-color:gray;width:100%;'>");

    QTextTable *dataTable = cursor.insertTable(
        ui->tableWidget->rowCount(),
        ui->tableWidget->columnCount(),
        tableList
        );


    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            QTextCursor cellCursor = dataTable->cellAt(row, col).firstCursorPosition();
            QWidget *widget = ui->tableWidget->cellWidget(row, col);
            if (widget) {
                QComboBox *comboBox = qobject_cast<QComboBox *>(widget);
                if (comboBox) {
                    cellCursor.insertBlock(formatLeft);
                    cellCursor.insertText(comboBox->currentText());
                } else {
                    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(widget);
                    if (lineEdit) {
                        cellCursor.insertBlock(formatLeft);
                        cellCursor.insertText(lineEdit->text());
                    }
                }
            }
        }
    }

    cursor.movePosition(QTextCursor::End);
    cursor.insertHtml("<hr style='height:2px;border:0;background-color:gray;width:100%;'>");

    cursor.insertBlock(formatLeft);
    cursor.insertText(QString("%1\t\t\t\t\t%2\n")
                          .arg(ui->labelSubTotal->text(), ui->subTotalDisplay->text()),
                      formatBold);

    cursor.insertBlock();
    cursor.insertText(QString("\t\t\t\t%1\t%2\n")
                          .arg(ui->labelTax->text(), ui->displayTax->text()),
                      formatBold);
    cursor.insertText(QString("\t\t\t\t%1\t%2\n")
                          .arg(ui->labelTotal->text(), ui->displayTotal->text()),
                      formatBold);


    QTextBlockFormat footerFormat;
    footerFormat.setAlignment(Qt::AlignLeft);
    footerFormat.setTopMargin(300);  // Increase as needed to push footer lower

    cursor.insertBlock(footerFormat);
    cursor.insertText(ui->thanksDisplay->text(), formatBold);

    printer.setPageMargins(QMarginsF(20, 15, 15, 15), QPageLayout::Millimeter);
    doc.print(&printer);
}

void MainWindow::on_pushButtonAdd_clicked()
{
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);

    QComboBox *comboBoxItems = new QComboBox();
    comboBoxItems->addItems({"", "Brand Consultation", "Logo Design", "Website Design", "Social media templates", "Brand photography", "Brand guide"});
    ui->tableWidget->setCellWidget(rowCount, 0, comboBoxItems);

    QLineEdit *lineEditQuantity = new QLineEdit();
    ui->tableWidget->setCellWidget(rowCount, 1, lineEditQuantity);

    QLineEdit *lineEditUnitPrice = new QLineEdit();
    ui->tableWidget->setCellWidget(rowCount, 2, lineEditUnitPrice);

    QLineEdit *lineEditPerTotal = new QLineEdit();
    lineEditPerTotal->setReadOnly(true);
    ui->tableWidget->setCellWidget(rowCount, 3, lineEditPerTotal);

    // Lambda to update total
    auto updateAll = [this]() {
        int subTotal = 0;
        int total = 0;

        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            auto combo = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(row, 0));
            auto qtyEdit = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(row, 1));
            auto unitEdit = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(row, 2));
            auto totalEdit = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(row, 3));

            if (!combo || !qtyEdit || !unitEdit || !totalEdit) continue;

            QString item = combo->currentText();
            QString qtyText = qtyEdit->text();

            if (itemsCost.contains(item) && !qtyText.isEmpty()) {
                int unitPrice = itemsCost[item];
                int qty = qtyText.toInt();
                int perItemTotal = unitPrice * qty;

                unitEdit->setText(QString::number(unitPrice));
                totalEdit->setText(QString::number(perItemTotal));

                subTotal += perItemTotal;
            }
        }
        total = subTotal - (subTotal / 10);
        ui->displayTotal->setText(QString::number(total));

        ui->subTotalDisplay->setText(QString::number(subTotal));
    };

    // Connect events
    connect(comboBoxItems, &QComboBox::currentTextChanged, this, updateAll);
    connect(lineEditQuantity, &QLineEdit::textChanged, this, updateAll);
}


void MainWindow::updateUnitPrice(const QString &itemName, QLineEdit *lineEditUnitPrice, QLineEdit *lineEditQuantity)
{
    int unitPrice = 0;
    int qty;
    if(itemsCost.contains(itemName))
    {
        unitPrice = itemsCost[itemName];
        lineEditUnitPrice->setText(QString::number(unitPrice));
    }
    qty = lineEditQuantity->text().toInt();
    qDebug()<<"lineEditQuantity"<<qty;
    qDebug()<<"lineEditUnitPrice"<<unitPrice;

}


void MainWindow::on_pushButtonDel_clicked()
{

}

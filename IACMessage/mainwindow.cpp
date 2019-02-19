#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>
#include <QJsonObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QAbstractButton::clicked, this, &MainWindow::button1Clicked);
    connect(ui->pushButton_2, &QAbstractButton::clicked, this, &MainWindow::button2Clicked);

    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);

    this->initItems();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initItems(){
    QString content;
    QFile file("../IACMessage/hmc_appservicetype.ini");
    QStringList items;
    if (file.open(QIODevice::ReadOnly)) { // If congif file exists,
        QTextStream stream(&file);
        content = stream.readAll();
        items = content.split('\n');
//        ui->plainTextEdit->setPlainText(content);
    }
    ui->comboBox->addItems(items);
    ui->comboBox_2->addItems(items);
}
void MainWindow::button1Clicked(){
    QString prefix, postfix;
    QString body = ui->textEdit->toPlainText();

    // Prefix + Body + Postfix
    if(ui->radioButton->isChecked()){ // 1:1
        prefix = ui->comboBox->currentText();
        postfix = ui->comboBox_2->currentText();
    } else if(ui->radioButton_2->isChecked()){ //1:N
        prefix = ui->comboBox->currentText();
        postfix = "APPS";
    } else if(ui->radioButton_3->isChecked()){//N:1
        prefix = "APP";
        postfix = ui->comboBox_2->currentText();
    } else if(ui->radioButton_4->isChecked()){//N:N
        prefix = "APP";
        postfix = "";
    } else if(ui->radioButton_5->isChecked()){//Braodcast
        prefix = "";
        postfix = "";
    }

    this->fullMessageName = prefix + "_" + body + "_" +postfix;
    this->fullMessageName = fullMessageName.toUpper();
    ui->label_9->setText(fullMessageName);

    setKeyValues();
}

void MainWindow::setKeyValues(){
    currentNum = ui->textEdit_4->toPlainText().toInt();

    for(int i=0;i<currentNum;i++){
//        QTextEdit *t1 = new QTextEdit();
        QHBoxLayout *layout = new QHBoxLayout;
        QLabel *label = new QLabel();
        label->setText(":");

        nameArray[i] = new QPlainTextEdit();
        nameArray[i]->setPlaceholderText("name");
        nameArray[i]->setFixedSize(100,31);

        typeArray[i] = new QComboBox();
        typeArray[i]->addItems({"string", "number", "json", "array", "boolean"});
        typeArray[i]->setFixedSize(100,31);

        layout->addWidget(nameArray[i]);
        layout->addWidget(label);
        layout->addWidget(typeArray[i]);

        ui->verticalLayout->addLayout(layout);
//        ui->verticalLayout->addWidget(nameArray[i]);
//        ui->verticalLayout->addWidget(typeArray[i]);

    }

}
void MainWindow::button2Clicked(){
    QJsonObject js;

    jsonMessage.append("\"" + fullMessageName + "\": {\n");

    for (int i=0; i<this->currentNum;i++) {
        QString name = nameArray[i]->toPlainText();
        QString defaultValue;

        if(typeArray[i]->currentText() == "string"){
            defaultValue = "\"\"";
        } else if(typeArray[i]->currentText() == "number"){
            defaultValue = "0";
        } else if(typeArray[i]->currentText() == "json"){
            defaultValue = "{}";
        } else if(typeArray[i]->currentText() == "array"){
            defaultValue = "[]";
        } else if(typeArray[i]->currentText() == "boolean"){
            defaultValue = "false";
        }

        if(i==this->currentNum-1){
            jsonMessage.append("\t\"" + name + "\" : "+ defaultValue + "\n");
        } else {
            jsonMessage.append("\t\"" + name + "\" : "+ defaultValue + ",\n");
        }
    }
    jsonMessage.append("}");

    jsonRuleMessage.append("\"" + fullMessageName + ".rule\": {\n");
    for (int i=0; i<this->currentNum;i++) {
        QString name = nameArray[i]->toPlainText();
        QString type = typeArray[i]->currentText();

        if(i==this->currentNum-1){
            jsonRuleMessage.append("\t\"" + name + "\" : \""+ type + "\"\n");
        } else {
            jsonRuleMessage.append("\t\"" + name + "\" : \""+ type + "\",\n");
        }
    }
    jsonRuleMessage.append("}");

    ui->plainTextEdit->setPlainText(jsonMessage + ",\n"+jsonRuleMessage);
}

void MainWindow::on_radioButton_clicked()
{
    ui->comboBox->setEnabled(true);
    ui->comboBox_2->setEnabled(true);

    // ui->plainTextEdit->setPlainText("Radio1 Clicked");
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->comboBox->setEnabled(true);
    ui->comboBox_2->setEnabled(false);
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(true);
}

void MainWindow::on_radioButton_4_clicked()
{
    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
}

void MainWindow::on_radioButton_5_clicked()
{
    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
}

void MainWindow::on_pushButton_3_clicked() // Clear all
{
     ui->plainTextEdit->clear();
     this->jsonMessage.clear();
     this->jsonRuleMessage.clear();
     QLayoutItem* item;
     QLayoutItem* item2;
     while ( ( item = ui->verticalLayout->takeAt(0)) != NULL ){
         QVBoxLayout *temp = (QVBoxLayout *)item;
         while((item2 = temp->takeAt(0)) != NULL){
             delete item2->widget();
             delete item2;
         }
         delete item->widget();
         delete item;
     }
}

void MainWindow::on_pushButton_4_clicked() // Save results to file
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out << text;
    file.close();
}

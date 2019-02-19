#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGroupBox>
#include <QPlainTextEdit>
#include <QComboBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initItems();
    void setKeyValues();
    QPlainTextEdit *nameArray[30];
    QComboBox *typeArray[30];
    int currentNum;

private slots:
    void button1Clicked();
    void button2Clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QString fullMessageName;
    QString jsonMessage;
    QString jsonRuleMessage;
};

#endif // MAINWINDOW_H

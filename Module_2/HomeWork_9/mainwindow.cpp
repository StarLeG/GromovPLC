#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    secondWindow = new SecondWindow();
    connect(this, &MainWindow::sendData, secondWindow, &SecondWindow::receiveData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_ok_clicked()
{
    QString number = ui->lineEdit->text();
    emit sendData(number);
    this->close();
    secondWindow->show();

    qDebug() << number;

}


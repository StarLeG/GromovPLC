#include "calculator.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Calculator calc;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    calc.reset();
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_btn_0_clicked()
{
    calc.digit(0);    
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_1_clicked()
{
    calc.digit(1);    
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_2_clicked()
{
    calc.digit(2);    
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_3_clicked()
{
    calc.digit(3);    
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_4_clicked()
{
    calc.digit(4);    
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_5_clicked()
{
    calc.digit(5);    
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_6_clicked()
{
    calc.digit(6);    
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_7_clicked()
{
    calc.digit(7);    
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_8_clicked()
{
    calc.digit(8);   
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_9_clicked()
{
    calc.digit(9);
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_rst_clicked()
{
    calc.reset();
    ui->scr->setText(calc.getDisplayString());
}

void MainWindow::on_btn_div_clicked()
{
    calc.operation(Calculator::Operation::Divide);
}

void MainWindow::on_btn_mul_clicked()
{
    calc.operation(Calculator::Operation::Multiply);
}

void MainWindow::on_btn_add_clicked()
{
    calc.operation(Calculator::Operation::Add);
}


void MainWindow::on_btn_sub_clicked()
{
    calc.operation(Calculator::Operation::Subtract);
}


void MainWindow::on_btn_eq_clicked()
{
    calc.calculate();    
    ui->scr->setText(calc.getDisplayString());

}


void MainWindow::on_btn_sing_clicked()
{
    calc.changeSign();   
    ui->scr->setText(calc.getDisplayString());
}


void MainWindow::on_btn_decimal_clicked()
{
    calc.setDecimal();    
    ui->scr->setText(calc.getDisplayString());
}


void MainWindow::on_btn_backSpace_clicked()
{
    calc.backspace();
    ui->scr->setText(calc.getDisplayString());
}


void MainWindow::on_btn_percentage_clicked()
{
    calc.percentage();
    ui->scr->setText(calc.getDisplayString());
}


void MainWindow::on_btn_mem_clicked()
{
    calc.memory();
}

void MainWindow::on_btn_memRecall_clicked()
{
    calc.memoryRecall();
    ui->scr->setText(calc.getDisplayString());
}


void MainWindow::on_btn_memClr_clicked()
{
    calc.memoryClear();
}


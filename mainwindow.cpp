#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    digitBTNs = {{Qt::Key_0, ui->btnNum0},
               {Qt::Key_1, ui->btnNum1},
               {Qt::Key_2, ui->btnNum2},
               {Qt::Key_3, ui->btnNum3},
               {Qt::Key_4, ui->btnNum4},
               {Qt::Key_5, ui->btnNum5},
               {Qt::Key_6, ui->btnNum6},
               {Qt::Key_7, ui->btnNum7},
               {Qt::Key_8, ui->btnNum8},
               {Qt::Key_9, ui->btnNum9},
            };

    foreach(auto btn,digitBTNs){
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    }

    // connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnMultable,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btndivision,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnminus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    connect(ui->btnPecentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquareroot,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnfraction,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnMaxOrMin,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::caculation(bool *ok)
{
    double result = 0;
    if (operands.size() >= 2 && !opcodes.isEmpty()) { // 允许 >=2 避免边界问题
        // 取操作数（按输入顺序计算，从左到右）
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        // 取运算符
        QString op = opcodes.front();
        opcodes.pop_front();

        // 计算逻辑
        if (op == "+") {
            result = operand1 + operand2;
        } else if (op == "-") {
            result = operand1 - operand2;
        } else if (op == "×") {
            result = operand1 * operand2;
        } else if (op == "÷") {
            if (operand2 == 0) {
                if (ok) *ok = false;
                return "Error"; // 处理除零错误
            }
            result = operand1 / operand2;
        }

        // 结果入栈（作为下一次运算的第一个操作数）
        operands.push_back(QString::number(result));
        ui->statusbar->showMessage("计算完成: " + QString::number(result));
    } else {
        ui->statusbar->showMessage("操作数或运算符不足");
    }

    return QString::number(result);
}

void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();

    if( digit == "0" && operand == "0")
        digit = "";

    if( operand == "0" && digit != "0")
        operand = "";

    operand += digit;
    ui->display->setText(operand);
}



void MainWindow::on_btnPoint_clicked()
{
    if(!operand.contains("."))
        operand+=qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(operand);
}


void MainWindow::on_btnDelete_clicked()
{
    operand = operand.left(operand.length()-1);
    ui->display->setText(operand);
}


void MainWindow::on_C_clicked()
{
    // 1. 清空所有与计算相关的变量/栈，彻底重置状态
    operand.clear();       // 清空当前输入的操作数（如“3”）
    operands.clear();      // 清空历史操作数栈（关键：清除上次残留的“2”）
    opcodes.clear();       // 清空运算符栈（避免残留运算符干扰）

    // 2. 清零后显示“0”（符合计算器常规逻辑，而非空白）
    operand = "0";         // 将当前操作数设为“0”，方便后续输入（如输入“3”时会自动覆盖“0”）
    ui->display->setText(operand);
}


void MainWindow::btnBinaryOperatorClicked()
{
    QString newOpcode = qobject_cast<QPushButton *>(sender())->text();

    // 1. 将当前输入的操作数入栈（如果有）
    if (!operand.isEmpty()) {
        operands.push_back(operand);
        operand.clear();
    }

    // 2. 若已有足够的操作数和运算符，先计算上一次的结果
    // （例如 "1+2" 后按 "+"，此时计算 1+2=3，结果作为下一次运算的第一个操作数）
    if (operands.size() >= 2 && !opcodes.isEmpty()) {
        caculation(); // 计算后 operands 中会只剩一个结果值
    }

    // 3. 存储新的运算符，用于下一次运算
    if (!operands.isEmpty()) {
        opcodes.push_back(newOpcode);
        // 显示当前结果（作为下一次运算的第一个操作数）
        ui->display->setText(operands.back());
    }
}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand != ""){
        double result = operand.toDouble();
        // operand = "";


        QString op = qobject_cast<QPushButton*>(sender())->text();

        if(op == "%"){
            result /= 100.0;
        }else if(op == "1/x"){
            result = 1/result;
        }else if(op == "x^2"){
            result = result * result;
        }else if(op == "√"){
            result = sqrt(result);
        }else if(op == "+/-"){
            result = -result; // 简化相反数逻辑
        }

        // 将计算结果存入operand，而非仅显示
        operand = QString::number(result);
        ui->display->setText(operand);
    }

}

void MainWindow::on_btnequal_clicked()
{
    // 1. 将当前输入的操作数入栈（如果有）
    if (!operand.isEmpty()) {
        operands.push_back(operand);
        operand.clear();
    }

    // 2. 计算所有剩余的运算（支持多步连续运算）
    while (operands.size() >= 2 && !opcodes.isEmpty()) {
        caculation();
    }

    // 3. 显示最终结果，并将结果作为下一次运算的起始值
    if (!operands.isEmpty()) {
        operand = operands.back(); // 保留结果用于后续运算
        ui->display->setText(operand);
        operands.clear(); // 清空栈，避免影响下一次运算
    } else {
        operand = "0";
        ui->display->setText(operand);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    foreach (auto btnKey, digitBTNs.keys()) {
        if(event->key()== btnKey){
            digitBTNs[btnKey]->animateClick();
        }
    }

    // if(event -> key() == Qt::Key_0)
    //     ui->btnNum0->animateClick();
    // else if (event -> key() == Qt::Key_1)
    //     ui->btnNum1->animateClick();

}



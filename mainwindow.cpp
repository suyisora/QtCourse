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
    if(operands.size() == 2 && opcodes.size() > 0){
    //取操作数
    double operand1 = operands.front().toDouble();
    operands.pop_front();
    double operand2 = operands.front().toDouble();
    operands.pop_front();


    //取操作符
    QString op = opcodes.front();
    opcodes.pop_front();

    if(op == "+"){
        result = operand1 + operand2;
    }else if(op == "-"){
        result = operand1 - operand2;
    }else if(op == "×"){
        result = operand1 * operand2;
    }else if(op == "÷"){
        result = operand1 / operand2;
    }


    operands.push_back(QString::number(result));

        ui->statusbar->showMessage(QString("caculation is in process:operand is %1,opcode is %2").arg(operands.size()).arg(opcodes.size()));
    }else{
        ui->statusbar->showMessage(QString("operand is %1,opcode is %2").arg(operands.size()).arg(opcodes.size()));
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
    QString opcode = qobject_cast<QPushButton *>(sender())->text();

    if(operand != ""){
        operands.push_back(operand);
        operand = "";

        opcodes.push_back(opcode);


        QString result = caculation();
        ui->display->setText(result);
    }
}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand != ""){
        double result = operand.toDouble();
        operand = "";

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
            if(result > 0) result = -result;
            else result = +result;
        }

        ui->display->setText(QString::number(result));
    }

}

void MainWindow::on_btnequal_clicked()
{
    if(operand != ""){
        operands.push_back(operand);
        operand = "";
    }

    QString result = caculation();
    ui->display->setText(result);
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



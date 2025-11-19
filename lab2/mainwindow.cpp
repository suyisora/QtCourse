#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "finddialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QColorDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textChanged = false;
    on_actionNew_triggered();

    statusLabel.setMaximumWidth(150);
    statusLabel.setText("length: " + QString::number(0) + "      lines: " + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMaximumWidth(150);
    statusCursorLabel.setText("Ln: " + QString::number(0) + "      Col: " + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("周锐铖"));
    ui->statusbar->addPermanentWidget(author);

    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionUndo->setEnabled(false);

    QPlainTextEdit::LineWrapMode mode = ui->TextEdit->lineWrapMode();
    if(mode == QTextEdit::NoWrap){
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionLineWrap->setChecked(true);
    }else{
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionLineWrap->setChecked(false);
    }
    ui->actionStatusBar->setChecked(true);
    ui->actionToolBar->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionFind_triggered()
{
    FindDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionReplace_triggered()
{
    ReplaceDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionNew_triggered()
{
    if(!userEditConfirmed())
        return;

    filePath = "";
    ui->TextEdit->clear();
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));

    textChanged = false;
}


void MainWindow::on_actionOpen_triggered()
{
    if(!userEditConfirmed())
        return;

    QString filename = QFileDialog::getOpenFileName(this,"打开文件",".",tr("Text file (*.txt) ;; All (*.*)"));
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "..","打开文件失败");
        return;
    }

    filePath = filename;

    QTextStream in(&file);
    QString text = in.readAll();
    ui->TextEdit->insertPlainText(text);
    file.close();
    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());

    textChanged = false;
}


void MainWindow::on_actionSave_triggered()//有点问题,保存逻辑，可优化
{
    if(filePath == ""){
        QString filename = QFileDialog::getSaveFileName(this,"保存文件",".",tr("Text file (*.txt)"));
        QFile file(filename);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "..","打开保存文件失败");
            return;
        }
        file.close();
        filePath = filename;
    }

    QFile file(filePath);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "..","打开文件失败");
        return;
    }

    /*if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "..","打开文件失败");

        QString filename = QFileDialog::getSaveFileName(this,"保存文件",".",tr("Text file (*.txt)"));
        QFile file(filename);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "..","打开保存文件失败");
            return;
        }
        filePath = filename;

    }*/

    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out << text;
    //std::cout << text.toStdString() << std::endl;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());

    textChanged = false;
}


void MainWindow::on_actionSaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"保存文件",".",tr("Text file (*.txt)"));
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "..","打开保存文件失败");
        return;
    }
    filePath = filename;
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out << text;
    //std::cout << text.toStdString() << std::endl;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
}


void MainWindow::on_TextEdit_textChanged()
{
    if(!textChanged){
        this->setWindowTitle("*" + this->windowTitle());
        textChanged = true;
    }
}

bool MainWindow::userEditConfirmed()
{
    if(textChanged){

        QString path = (filePath != "") ? filePath : "无标题.txt";

        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("...");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改保存到\n") + "\"" + path + "\" ?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int r=msg.exec();
        switch(r){
        case QMessageBox::Yes:
            on_actionSave_triggered();
            break;
        case QMessageBox::No:
            textChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;
        }
    }
    return true;
}


void MainWindow::on_actionUndo_triggered()
{
    ui->TextEdit->undo();
}


void MainWindow::on_actionCut_triggered()
{
    ui->TextEdit->cut();
    ui->actionPaste->setEnabled(true);
}


void MainWindow::on_actionCopy_triggered()
{
    ui->TextEdit->copy();
    ui->actionPaste->setEnabled(true);
}


void MainWindow::on_actionPaste_triggered()
{
    ui->TextEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->TextEdit->redo();
}


void MainWindow::on_TextEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
}


void MainWindow::on_TextEdit_redoAvailable(bool b)
{
    ui->actionRedo->setEnabled(b);
}


void MainWindow::on_TextEdit_undoAvailable(bool b)
{
    ui->actionUndo->setEnabled(b);
}


void MainWindow::on_actionFontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if(color.isValid()){
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit {color: %1}").arg(color.name()));
    }
}


void MainWindow::on_actionEditorColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if(color.isValid()){
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit {background-color: %1}").arg(color.name()));
    }
}


void MainWindow::on_actionBackgroundColor_triggered()
{

}


void MainWindow::on_actionLineWrap_triggered()
{
    QPlainTextEdit::LineWrapMode mode = ui->TextEdit->lineWrapMode();
    if(mode==QTextEdit::NoWrap){
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionLineWrap->setChecked(true);
    }else{
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionLineWrap->setChecked(false);
    }
}


void MainWindow::on_actionFont_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
        ui->TextEdit->setFont(font);
}


void MainWindow::on_actionToolBar_triggered()
{
    bool visible = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->actionToolBar->setChecked(!visible);
}


void MainWindow::on_actionStatusBar_triggered()
{
    bool visible = ui->statusbar->isVisible();
    ui->statusbar->setVisible(!visible);
    ui->actionStatusBar->setChecked(!visible);
}


void MainWindow::on_actionExit_triggered()
{
    if(userEditConfirmed())
        exit(0);

}


void MainWindow::on_actionSelectAll_triggered()
{
    ui->TextEdit->selectAll();
}


#include "addwindow.h"
#include "ui_addwindow.h"
#include <QMessageBox>

AddWindow::AddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddWindow)
{
    ui->setupUi(this);

    // 初始化下拉框选项
    ui->comboCategory->addItems({"社交娱乐", "工作办公", "其他"});
}

AddWindow::~AddWindow()
{
    delete ui;
}

QString AddWindow::getCategory() const
{
    return ui->comboCategory->currentText();
}

QString AddWindow::getSite() const
{
    return ui->lineSite->text();
}

QString AddWindow::getUser() const
{
    return ui->lineUser->text();
}

QString AddWindow::getPassword() const
{
    return ui->linePass->text();
}

QString AddWindow::getNote() const
{
    return ui->lineNote->text();
}




void AddWindow::on_btnSave_clicked()
{
    // 简单校验：网站和密码不能为空
    if(ui->lineSite->text().isEmpty() || ui->linePass->text().isEmpty()) {
        QMessageBox::warning(this, "提示", "网站和密码不能为空！");
        return;
    }
    // 关闭窗口，返回 Accepted 状态
    accept();
}


void AddWindow::on_btnCancel_clicked()
{
    // 关闭窗口，返回 Rejected 状态
    reject();
}

void AddWindow::setData(const QString &category, const QString &site,
                        const QString &user, const QString &pass, const QString &note)
{
    ui->comboCategory->setCurrentText(category);
    ui->lineSite->setText(site);
    ui->lineUser->setText(user);
    ui->linePass->setText(pass); // 注意：这里传入的应该是解密后的明文
    ui->lineNote->setText(note);

    this->setWindowTitle("编辑账号信息"); // 修改窗口标题
}


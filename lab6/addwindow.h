#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>

namespace Ui {
class AddWindow;
}

class AddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddWindow(QWidget *parent = nullptr);
    ~AddWindow();

    // 提供获取用户输入数据的接口
    QString getCategory() const;
    QString getSite() const;
    QString getUser() const;
    QString getPassword() const;
    QString getNote() const;

    // 初始化数据
    void setData(const QString &category, const QString &site,
                 const QString &user, const QString &pass, const QString &note);

private slots:
    void on_btnSave_clicked();   // 点击保存
    void on_btnCancel_clicked(); // 点击取消


private:
    Ui::AddWindow *ui;
};

#endif // ADDWINDOW_H

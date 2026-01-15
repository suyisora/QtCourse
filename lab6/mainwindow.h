#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "addwindow.h"
#include <QtConcurrent>
#include <QFutureWatcher>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initSideBar();//初始化选项函数

private slots:
    void on_actionAdd_triggered();
    void on_listWidgetCategories_currentTextChanged(const QString &currentText);
    void on_searchEdit_textChanged(const QString &arg1);
    void showContextMenu(const QPoint &pos);
    void on_actionDel_triggered();

    void on_actionExport_triggered();
    void onExportFinished();

    void on_actionImport_triggered();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *m_model;//声明数据模型指针
    void initTableView();//初始化表格函数
    void saveAccountToDb(AddWindow &dlg);

    QFutureWatcher<void> m_watcher;

};
#endif // MAINWINDOW_H

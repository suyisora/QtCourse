#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStack>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>

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

    QString operand;
    QStack<QString> operands;

    QString opcode;
    QStack<QString> opcodes;

    QMap<int, QPushButton*> digitBTNs;

    QString caculation(bool *ok=NULL);

private slots:
    void btnNumClicked();
    void btnBinaryOperatorClicked();
    void btnUnaryOperatorClicked();

    void on_btnPoint_clicked();

    void on_btnDelete_clicked();

    void on_C_clicked();

    void on_btnequal_clicked();

    virtual void keyPressEvent(QKeyEvent *event);

    void on_CE_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

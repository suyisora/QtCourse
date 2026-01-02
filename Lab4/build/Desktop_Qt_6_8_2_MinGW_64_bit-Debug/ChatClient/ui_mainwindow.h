/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QStackedWidget *stackedWidget;
    QWidget *chatPage;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QTextEdit *roomtextEdit;
    QListWidget *userlistWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *saylineEdit;
    QPushButton *sayButton;
    QPushButton *layoutButton;
    QWidget *loginPage;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QFrame *loginFrame;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *mainFrame;
    QLabel *label_2;
    QLineEdit *serverEdit;
    QLabel *label_3;
    QLineEdit *usernameEdit;
    QSpacerItem *verticalSpacer;
    QPushButton *loginButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(595, 428);
        MainWindow->setStyleSheet(QString::fromUtf8("#titleLabel {\n"
"    background: white;\n"
"    border: none;\n"
"    border-bottom: 1px solid black;\n"
"    border-top: 1px solid black;\n"
"    font: 24pt \"\351\273\221\344\275\223\";\n"
"    color: rgba(255, 255, 255, 1);\n"
"    background-color: rgba(0, 170, 127, 255);\n"
"}\n"
"\n"
"#mainFrame {\n"
"    background: white;\n"
"    border: none;\n"
"}\n"
"\n"
"#loginFrame {\n"
"    background: linear-gradient(to top, rgba(0, 170, 127, 0.2), rgba(0, 170, 127, 0.2));\n"
"    border: 1px solid gray;\n"
"    padding: 10px;\n"
"    border-radius: 25px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setStyleSheet(QString::fromUtf8("#titleLabel {\n"
"    background: white;\n"
"    border: none;\n"
"    border-bottom: 1px solid black;\n"
"    border-top: 1px solid black;\n"
"    font: 24pt \"\351\273\221\344\275\223\";\n"
"    color: rgba(255, 255, 255, 1);\n"
"    background-color: rgba(0, 170, 127, 255);\n"
"}\n"
"\n"
"#mainFrame {\n"
"    background: white;\n"
"    border: none;\n"
"}\n"
"\n"
"#loginFrame {\n"
"    background: linear-gradient(to top, rgba(0, 170, 127, 0.2), rgba(0, 170, 127, 0.2));\n"
"    border: 1px solid gray;\n"
"    padding: 10px;\n"
"    border-radius: 25px;\n"
"}"));

        verticalLayout->addWidget(titleLabel);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        chatPage = new QWidget();
        chatPage->setObjectName("chatPage");
        verticalLayout_3 = new QVBoxLayout(chatPage);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        roomtextEdit = new QTextEdit(chatPage);
        roomtextEdit->setObjectName("roomtextEdit");

        horizontalLayout->addWidget(roomtextEdit);

        userlistWidget = new QListWidget(chatPage);
        userlistWidget->setObjectName("userlistWidget");
        userlistWidget->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(userlistWidget);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        saylineEdit = new QLineEdit(chatPage);
        saylineEdit->setObjectName("saylineEdit");

        horizontalLayout_2->addWidget(saylineEdit);

        sayButton = new QPushButton(chatPage);
        sayButton->setObjectName("sayButton");

        horizontalLayout_2->addWidget(sayButton);

        layoutButton = new QPushButton(chatPage);
        layoutButton->setObjectName("layoutButton");

        horizontalLayout_2->addWidget(layoutButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(chatPage);
        loginPage = new QWidget();
        loginPage->setObjectName("loginPage");
        gridLayout = new QGridLayout(loginPage);
        gridLayout->setObjectName("gridLayout");
        verticalSpacer_2 = new QSpacerItem(20, 123, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(175, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        loginFrame = new QFrame(loginPage);
        loginFrame->setObjectName("loginFrame");
        loginFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 230, 255);"));
        loginFrame->setFrameShape(QFrame::Shape::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(loginFrame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        mainFrame = new QFormLayout();
        mainFrame->setObjectName("mainFrame");
        label_2 = new QLabel(loginFrame);
        label_2->setObjectName("label_2");

        mainFrame->setWidget(0, QFormLayout::LabelRole, label_2);

        serverEdit = new QLineEdit(loginFrame);
        serverEdit->setObjectName("serverEdit");

        mainFrame->setWidget(0, QFormLayout::FieldRole, serverEdit);

        label_3 = new QLabel(loginFrame);
        label_3->setObjectName("label_3");

        mainFrame->setWidget(1, QFormLayout::LabelRole, label_3);

        usernameEdit = new QLineEdit(loginFrame);
        usernameEdit->setObjectName("usernameEdit");

        mainFrame->setWidget(1, QFormLayout::FieldRole, usernameEdit);


        verticalLayout_2->addLayout(mainFrame);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName("loginButton");

        verticalLayout_2->addWidget(loginButton);


        gridLayout->addWidget(loginFrame, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(174, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 123, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 2, 1, 1, 1);

        stackedWidget->addWidget(loginPage);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\201\212\345\244\251\345\256\244\345\256\242\346\210\267\347\253\257", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\351\231\210\344\274\237\351\224\213\347\232\204\350\201\212\345\244\251\345\256\244", nullptr));
        sayButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        layoutButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        serverEdit->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\230\265\347\247\260\357\274\232", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225\350\201\212\345\244\251\345\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

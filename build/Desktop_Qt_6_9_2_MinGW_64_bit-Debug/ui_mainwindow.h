/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QPushButton *btnSquare;
    QPushButton *btnPoint;
    QPushButton *btnminus;
    QPushButton *btnMaxOrMin;
    QPushButton *btnPecentage;
    QPushButton *btnNum4;
    QPushButton *C;
    QPushButton *btnSquareroot;
    QPushButton *btnequal;
    QPushButton *btnNum0;
    QPushButton *btnNum1;
    QPushButton *btnNum8;
    QPushButton *btnNum3;
    QPushButton *btnfraction;
    QPushButton *btnNum5;
    QPushButton *CE;
    QPushButton *btnNum6;
    QPushButton *btnDelete;
    QPushButton *btnNum9;
    QPushButton *btndivision;
    QPushButton *btnNum7;
    QPushButton *btnMultable;
    QPushButton *btnPlus;
    QPushButton *btnNum2;
    QLineEdit *display;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(767, 592);
        MainWindow->setMaximumSize(QSize(16777, 16777));
        MainWindow->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	font: 11pt \"Lucida Sans Unicode\";\n"
"	background-color: rgb(255,255,224);\n"
"	font-size: 15pt;\n"
"	color: black;\n"
"	border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: rgb(255,239,213);\n"
"	color: black;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: rgb(189,183,107);\n"
"	color: black;\n"
"}\n"
"\n"
"QLineEdit{\n"
"	font-size:20pt;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        gridLayout->setHorizontalSpacing(7);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        btnSquare = new QPushButton(centralwidget);
        btnSquare->setObjectName("btnSquare");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnSquare->sizePolicy().hasHeightForWidth());
        btnSquare->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnSquare, 2, 1, 1, 1);

        btnPoint = new QPushButton(centralwidget);
        btnPoint->setObjectName("btnPoint");
        sizePolicy1.setHeightForWidth(btnPoint->sizePolicy().hasHeightForWidth());
        btnPoint->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnPoint, 6, 2, 1, 1);

        btnminus = new QPushButton(centralwidget);
        btnminus->setObjectName("btnminus");
        sizePolicy1.setHeightForWidth(btnminus->sizePolicy().hasHeightForWidth());
        btnminus->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnminus, 4, 3, 1, 1);

        btnMaxOrMin = new QPushButton(centralwidget);
        btnMaxOrMin->setObjectName("btnMaxOrMin");
        sizePolicy1.setHeightForWidth(btnMaxOrMin->sizePolicy().hasHeightForWidth());
        btnMaxOrMin->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnMaxOrMin, 6, 0, 1, 1);

        btnPecentage = new QPushButton(centralwidget);
        btnPecentage->setObjectName("btnPecentage");
        sizePolicy1.setHeightForWidth(btnPecentage->sizePolicy().hasHeightForWidth());
        btnPecentage->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnPecentage, 1, 0, 1, 1);

        btnNum4 = new QPushButton(centralwidget);
        btnNum4->setObjectName("btnNum4");
        sizePolicy1.setHeightForWidth(btnNum4->sizePolicy().hasHeightForWidth());
        btnNum4->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnNum4, 4, 0, 1, 1);

        C = new QPushButton(centralwidget);
        C->setObjectName("C");
        sizePolicy1.setHeightForWidth(C->sizePolicy().hasHeightForWidth());
        C->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(C, 1, 2, 1, 1);

        btnSquareroot = new QPushButton(centralwidget);
        btnSquareroot->setObjectName("btnSquareroot");
        sizePolicy1.setHeightForWidth(btnSquareroot->sizePolicy().hasHeightForWidth());
        btnSquareroot->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnSquareroot, 2, 2, 1, 1);

        btnequal = new QPushButton(centralwidget);
        btnequal->setObjectName("btnequal");
        sizePolicy1.setHeightForWidth(btnequal->sizePolicy().hasHeightForWidth());
        btnequal->setSizePolicy(sizePolicy1);
        btnequal->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft Tai Le\";\n"
"background-color:rgb(0,255,255)"));

        gridLayout->addWidget(btnequal, 6, 3, 1, 1);

        btnNum0 = new QPushButton(centralwidget);
        btnNum0->setObjectName("btnNum0");
        sizePolicy1.setHeightForWidth(btnNum0->sizePolicy().hasHeightForWidth());
        btnNum0->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnNum0, 6, 1, 1, 1);

        btnNum1 = new QPushButton(centralwidget);
        btnNum1->setObjectName("btnNum1");
        sizePolicy1.setHeightForWidth(btnNum1->sizePolicy().hasHeightForWidth());
        btnNum1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnNum1, 5, 0, 1, 1);

        btnNum8 = new QPushButton(centralwidget);
        btnNum8->setObjectName("btnNum8");
        sizePolicy1.setHeightForWidth(btnNum8->sizePolicy().hasHeightForWidth());
        btnNum8->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnNum8, 3, 1, 1, 1);

        btnNum3 = new QPushButton(centralwidget);
        btnNum3->setObjectName("btnNum3");
        sizePolicy1.setHeightForWidth(btnNum3->sizePolicy().hasHeightForWidth());
        btnNum3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnNum3, 5, 2, 1, 1);

        btnfraction = new QPushButton(centralwidget);
        btnfraction->setObjectName("btnfraction");
        sizePolicy1.setHeightForWidth(btnfraction->sizePolicy().hasHeightForWidth());
        btnfraction->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnfraction, 2, 0, 1, 1);

        btnNum5 = new QPushButton(centralwidget);
        btnNum5->setObjectName("btnNum5");
        sizePolicy1.setHeightForWidth(btnNum5->sizePolicy().hasHeightForWidth());
        btnNum5->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnNum5, 4, 1, 1, 1);

        CE = new QPushButton(centralwidget);
        CE->setObjectName("CE");
        sizePolicy1.setHeightForWidth(CE->sizePolicy().hasHeightForWidth());
        CE->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(CE, 1, 1, 1, 1);

        btnNum6 = new QPushButton(centralwidget);
        btnNum6->setObjectName("btnNum6");
        sizePolicy1.setHeightForWidth(btnNum6->sizePolicy().hasHeightForWidth());
        btnNum6->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnNum6, 4, 2, 1, 1);

        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName("btnDelete");
        sizePolicy1.setHeightForWidth(btnDelete->sizePolicy().hasHeightForWidth());
        btnDelete->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnDelete, 1, 3, 1, 1);

        btnNum9 = new QPushButton(centralwidget);
        btnNum9->setObjectName("btnNum9");
        sizePolicy1.setHeightForWidth(btnNum9->sizePolicy().hasHeightForWidth());
        btnNum9->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnNum9, 3, 2, 1, 1);

        btndivision = new QPushButton(centralwidget);
        btndivision->setObjectName("btndivision");
        sizePolicy1.setHeightForWidth(btndivision->sizePolicy().hasHeightForWidth());
        btndivision->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btndivision, 2, 3, 1, 1);

        btnNum7 = new QPushButton(centralwidget);
        btnNum7->setObjectName("btnNum7");
        sizePolicy1.setHeightForWidth(btnNum7->sizePolicy().hasHeightForWidth());
        btnNum7->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnNum7, 3, 0, 1, 1);

        btnMultable = new QPushButton(centralwidget);
        btnMultable->setObjectName("btnMultable");
        sizePolicy1.setHeightForWidth(btnMultable->sizePolicy().hasHeightForWidth());
        btnMultable->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnMultable, 3, 3, 1, 1);

        btnPlus = new QPushButton(centralwidget);
        btnPlus->setObjectName("btnPlus");
        sizePolicy1.setHeightForWidth(btnPlus->sizePolicy().hasHeightForWidth());
        btnPlus->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnPlus, 5, 3, 1, 1);

        btnNum2 = new QPushButton(centralwidget);
        btnNum2->setObjectName("btnNum2");
        sizePolicy1.setHeightForWidth(btnNum2->sizePolicy().hasHeightForWidth());
        btnNum2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnNum2, 5, 1, 1, 1);

        display = new QLineEdit(centralwidget);
        display->setObjectName("display");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(display->sizePolicy().hasHeightForWidth());
        display->setSizePolicy(sizePolicy2);
        display->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(display, 0, 0, 1, 4);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 767, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\345\231\250_\345\221\250\345\256\207\350\201\252_2023414290243", nullptr));
        btnSquare->setText(QCoreApplication::translate("MainWindow", "x^2", nullptr));
        btnPoint->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        btnminus->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        btnMaxOrMin->setText(QCoreApplication::translate("MainWindow", "+/-", nullptr));
        btnPecentage->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        btnNum4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        C->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        btnSquareroot->setText(QCoreApplication::translate("MainWindow", "\342\210\232", nullptr));
        btnequal->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        btnNum0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnNum1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btnNum8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btnNum3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btnfraction->setText(QCoreApplication::translate("MainWindow", "1/x", nullptr));
        btnNum5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        CE->setText(QCoreApplication::translate("MainWindow", "CE", nullptr));
        btnNum6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btnDelete->setText(QCoreApplication::translate("MainWindow", "\342\214\253", nullptr));
        btnNum9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btndivision->setText(QCoreApplication::translate("MainWindow", "\303\267", nullptr));
        btnNum7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btnMultable->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        btnPlus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnNum2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        display->setPlaceholderText(QCoreApplication::translate("MainWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

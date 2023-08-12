/********************************************************************************
** Form generated from reading UI file 'four.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOUR_H
#define UI_FOUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fourClass
{
public:
    QWidget* centralWidget;
    QGridLayout* gridLayout_2;
    QGridLayout* gridLayout_1;
    QGridLayout* gridLayout;
    QGraphicsView* graphicsView;
    QGraphicsView* graphicsView_2;
    QLabel* label_1;
    QLabel* label_2;
    QMenuBar* menuBar;
    QToolBar* mainToolBar;
    QStatusBar* statusBar;
    QPushButton* rstpushbutton;
    QPushButton* openpushbutton;
    QPushButton* closepushbutton;
    QPushButton* flippushbutton;

    void setupUi(QMainWindow* fourClass)
    {
        if (fourClass->objectName().isEmpty())
            fourClass->setObjectName(QStringLiteral("fourClass"));
        fourClass->resize(1230, 450);
        centralWidget = new QWidget(fourClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));

        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 5);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        gridLayout_1 = new QGridLayout();
        gridLayout_1->setSpacing(6);
        gridLayout_1->setObjectName(QStringLiteral("gridLayout_1"));

        label_1 = new QLabel(QString::fromLocal8Bit("机器人头部图像"));
        label_1->setObjectName(QStringLiteral("label_1"));

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        label_2 = new QLabel(QString::fromLocal8Bit("机器人尾部图像"));
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 1, 0, 1, 1);

        graphicsView_2 = new QGraphicsView(centralWidget);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));

        gridLayout->addWidget(graphicsView_2, 1, 1, 1, 1);

        rstpushbutton = new QPushButton(QString::fromLocal8Bit("复位"));
        rstpushbutton->setObjectName(QStringLiteral("rstpushbutton"));

        gridLayout_1->addWidget(rstpushbutton, 0, 0, 1, 1);

        flippushbutton = new QPushButton(QString::fromLocal8Bit("翻转"));
        flippushbutton->setObjectName(QStringLiteral("flippushbutton"));

        gridLayout_1->addWidget(flippushbutton, 0, 1, 1, 1);

        openpushbutton = new QPushButton(QString::fromLocal8Bit("开始录制"));
        openpushbutton->setObjectName(QStringLiteral("openpushbutton"));

        gridLayout_1->addWidget(openpushbutton, 0, 2, 1, 1);

        closepushbutton = new QPushButton(QString::fromLocal8Bit("结束录制"));
        closepushbutton->setObjectName(QStringLiteral("closepushbutton"));

        gridLayout_1->addWidget(closepushbutton, 0, 3, 1, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);
        gridLayout_2->addLayout(gridLayout_1, 1, 0, 1, 1);

        fourClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(fourClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 648, 23));
        fourClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(fourClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        fourClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(fourClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        fourClass->setStatusBar(statusBar);

        retranslateUi(fourClass);

        QMetaObject::connectSlotsByName(fourClass);
    } // setupUi

    void retranslateUi(QMainWindow* fourClass)
    {
        fourClass->setWindowTitle(QString::fromLocal8Bit("叶片机器人摄像界面"));//标题设置
    } // retranslateUi
    
};

namespace Ui {
    class fourClass : public Ui_fourClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOUR_H


/********************************************************************************
** Form generated from reading UI file 'pose_re.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSE_RE_H
#define UI_POSE_RE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Pose_ReClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QProgressBar *progressBar;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Pose_ReClass)
    {
        if (Pose_ReClass->objectName().isEmpty())
            Pose_ReClass->setObjectName(QStringLiteral("Pose_ReClass"));
        Pose_ReClass->resize(1055, 814);
        centralWidget = new QWidget(Pose_ReClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 200, 501, 361));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(40, 700, 641, 23));
        progressBar->setValue(24);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(860, 50, 321, 471));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 10, 131, 31));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(750, 10, 111, 31));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(420, 10, 121, 31));
        Pose_ReClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Pose_ReClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1055, 23));
        Pose_ReClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Pose_ReClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Pose_ReClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Pose_ReClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Pose_ReClass->setStatusBar(statusBar);

        retranslateUi(Pose_ReClass);
        QObject::connect(pushButton, SIGNAL(clicked()), Pose_ReClass, SLOT(Begin_Test()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), Pose_ReClass, SLOT(Stop_Systeam()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), Pose_ReClass, SLOT(Save_Result()));

        QMetaObject::connectSlotsByName(Pose_ReClass);
    } // setupUi

    void retranslateUi(QMainWindow *Pose_ReClass)
    {
        Pose_ReClass->setWindowTitle(QApplication::translate("Pose_ReClass", "Pose_Re", 0));
        label->setText(QApplication::translate("Pose_ReClass", "TextLabel", 0));
        pushButton->setText(QApplication::translate("Pose_ReClass", "\345\274\200\345\247\213\346\265\213\350\257\225", 0));
        pushButton_2->setText(QApplication::translate("Pose_ReClass", "\351\200\200\345\207\272\347\263\273\347\273\237", 0));
        pushButton_3->setText(QApplication::translate("Pose_ReClass", "\344\277\235\345\255\230\347\273\223\346\236\234", 0));
    } // retranslateUi

};

namespace Ui {
    class Pose_ReClass: public Ui_Pose_ReClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSE_RE_H

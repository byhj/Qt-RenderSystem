/********************************************************************************
** Form generated from reading UI file 'rendersystem.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERSYSTEM_H
#define UI_RENDERSYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenderSystemClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RenderSystemClass)
    {
        if (RenderSystemClass->objectName().isEmpty())
            RenderSystemClass->setObjectName(QStringLiteral("RenderSystemClass"));
        RenderSystemClass->resize(1134, 846);
        RenderSystemClass->setWindowOpacity(1);
        RenderSystemClass->setStyleSheet(QStringLiteral("color: black;"));
        centralWidget = new QWidget(RenderSystemClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        RenderSystemClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RenderSystemClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1134, 26));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        RenderSystemClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(RenderSystemClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RenderSystemClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());

        retranslateUi(RenderSystemClass);

        QMetaObject::connectSlotsByName(RenderSystemClass);
    } // setupUi

    void retranslateUi(QMainWindow *RenderSystemClass)
    {
        RenderSystemClass->setWindowTitle(QApplication::translate("RenderSystemClass", "RenderSystem", 0));
        menuHelp->setTitle(QApplication::translate("RenderSystemClass", "Help", 0));
        menuFile->setTitle(QApplication::translate("RenderSystemClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class RenderSystemClass: public Ui_RenderSystemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERSYSTEM_H

/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created: Mon Sep 6 18:59:44 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openAction;
    QAction *exitAction;
    QAction *increaseScaleAction;
    QAction *decreaseScaleAction;
    QAction *documentControlsAction;
    QAction *selectedTextAction;
    QAction *actionSearch;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *_2;
    QLabel *pageLabel;
    QSpinBox *pageSpinBox;
    QComboBox *scaleComboBox;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;
    QDockWidget *searchDockWidget;
    QWidget *dockWidgetContents_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *searchLabel;
    QLineEdit *searchLineEdit;
    QPushButton *findButton;
    QComboBox *searchComboBox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(858, 600);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks);
        openAction = new QAction(MainWindow);
        openAction->setObjectName(QString::fromUtf8("openAction"));
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        increaseScaleAction = new QAction(MainWindow);
        increaseScaleAction->setObjectName(QString::fromUtf8("increaseScaleAction"));
        decreaseScaleAction = new QAction(MainWindow);
        decreaseScaleAction->setObjectName(QString::fromUtf8("decreaseScaleAction"));
        documentControlsAction = new QAction(MainWindow);
        documentControlsAction->setObjectName(QString::fromUtf8("documentControlsAction"));
        documentControlsAction->setCheckable(true);
        documentControlsAction->setChecked(true);
        selectedTextAction = new QAction(MainWindow);
        selectedTextAction->setObjectName(QString::fromUtf8("selectedTextAction"));
        selectedTextAction->setCheckable(true);
        selectedTextAction->setChecked(true);
        actionSearch = new QAction(MainWindow);
        actionSearch->setObjectName(QString::fromUtf8("actionSearch"));
        actionSearch->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 852, 292));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        _2 = new QHBoxLayout();
        _2->setObjectName(QString::fromUtf8("_2"));
        pageLabel = new QLabel(centralwidget);
        pageLabel->setObjectName(QString::fromUtf8("pageLabel"));

        _2->addWidget(pageLabel);

        pageSpinBox = new QSpinBox(centralwidget);
        pageSpinBox->setObjectName(QString::fromUtf8("pageSpinBox"));
        pageSpinBox->setEnabled(false);

        _2->addWidget(pageSpinBox);


        horizontalLayout->addLayout(_2);

        scaleComboBox = new QComboBox(centralwidget);
        scaleComboBox->setObjectName(QString::fromUtf8("scaleComboBox"));
        scaleComboBox->setEnabled(false);

        horizontalLayout->addWidget(scaleComboBox);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 858, 21));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        searchDockWidget = new QDockWidget(MainWindow);
        searchDockWidget->setObjectName(QString::fromUtf8("searchDockWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(searchDockWidget->sizePolicy().hasHeightForWidth());
        searchDockWidget->setSizePolicy(sizePolicy1);
        searchDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        horizontalLayout_3 = new QHBoxLayout(dockWidgetContents_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        searchLabel = new QLabel(dockWidgetContents_3);
        searchLabel->setObjectName(QString::fromUtf8("searchLabel"));
        searchLabel->setTextFormat(Qt::AutoText);

        horizontalLayout_3->addWidget(searchLabel);

        searchLineEdit = new QLineEdit(dockWidgetContents_3);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setEnabled(false);

        horizontalLayout_3->addWidget(searchLineEdit);

        findButton = new QPushButton(dockWidgetContents_3);
        findButton->setObjectName(QString::fromUtf8("findButton"));
        findButton->setEnabled(false);

        horizontalLayout_3->addWidget(findButton);

        searchComboBox = new QComboBox(dockWidgetContents_3);
        searchComboBox->setObjectName(QString::fromUtf8("searchComboBox"));
        searchComboBox->setEnabled(false);

        horizontalLayout_3->addWidget(searchComboBox);

        searchDockWidget->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), searchDockWidget);
#ifndef QT_NO_SHORTCUT
        pageLabel->setBuddy(pageSpinBox);
        searchLabel->setBuddy(searchLineEdit);
#endif // QT_NO_SHORTCUT

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(openAction);
        menu_File->addAction(actionSearch);

        retranslateUi(MainWindow);

        scaleComboBox->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PDF Viewer", 0, QApplication::UnicodeUTF8));
        openAction->setText(QApplication::translate("MainWindow", "&Open...", 0, QApplication::UnicodeUTF8));
        openAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        exitAction->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        increaseScaleAction->setText(QApplication::translate("MainWindow", "&Increase Scale", 0, QApplication::UnicodeUTF8));
        increaseScaleAction->setShortcut(QApplication::translate("MainWindow", "Ctrl++", 0, QApplication::UnicodeUTF8));
        decreaseScaleAction->setText(QApplication::translate("MainWindow", "&Decrease Scale", 0, QApplication::UnicodeUTF8));
        decreaseScaleAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0, QApplication::UnicodeUTF8));
        documentControlsAction->setText(QApplication::translate("MainWindow", "&Document Controls", 0, QApplication::UnicodeUTF8));
        selectedTextAction->setText(QApplication::translate("MainWindow", "&Selected Text", 0, QApplication::UnicodeUTF8));
        actionSearch->setText(QApplication::translate("MainWindow", "&Search", 0, QApplication::UnicodeUTF8));
        actionSearch->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        pageLabel->setText(QApplication::translate("MainWindow", "&Page:", 0, QApplication::UnicodeUTF8));
        scaleComboBox->clear();
        scaleComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "25%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "50%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "75%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "100%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "125%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "150%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "200%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "300%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "400%", 0, QApplication::UnicodeUTF8)
        );
        menu_File->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
        searchLabel->setText(QApplication::translate("MainWindow", "&Search:", 0, QApplication::UnicodeUTF8));
        findButton->setText(QApplication::translate("MainWindow", "&Find", 0, QApplication::UnicodeUTF8));
        searchComboBox->clear();
        searchComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Forwards", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Backwards", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H

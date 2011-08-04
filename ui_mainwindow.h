/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 3. Aug 22:12:31 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClearConsole;
    QAction *actionQuit;
    QAction *actionTimeouts;
    QAction *actionColor_palette;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *cbPort;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QComboBox *cbSpeed;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *openButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QTabWidget *tabWidget;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Settings;
    QMenu *menuCheck;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(700, 521);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/qt-logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setWindowOpacity(1);
        MainWindow->setIconSize(QSize(24, 24));
        actionClearConsole = new QAction(MainWindow);
        actionClearConsole->setObjectName(QString::fromUtf8("actionClearConsole"));
        actionClearConsole->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/edit-clear-2.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/files/D:/\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\270/crystal_clear_icons/png/32x32/filesystems/folder_green.png"), QSize(), QIcon::Normal, QIcon::On);
        actionClearConsole->setIcon(icon1);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionQuit->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/application-exit-2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon2);
        actionTimeouts = new QAction(MainWindow);
        actionTimeouts->setObjectName(QString::fromUtf8("actionTimeouts"));
        actionTimeouts->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/draw-path.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTimeouts->setIcon(icon3);
        actionColor_palette = new QAction(MainWindow);
        actionColor_palette->setObjectName(QString::fromUtf8("actionColor_palette"));
        actionColor_palette->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/document-save-5.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionColor_palette->setIcon(icon4);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(9);
        label->setFont(font);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        cbPort = new QComboBox(groupBox);
        cbPort->setObjectName(QString::fromUtf8("cbPort"));
        sizePolicy.setHeightForWidth(cbPort->sizePolicy().hasHeightForWidth());
        cbPort->setSizePolicy(sizePolicy);
        cbPort->setMaximumSize(QSize(16777213, 20));

        horizontalLayout->addWidget(cbPort);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        cbSpeed = new QComboBox(groupBox);
        cbSpeed->setObjectName(QString::fromUtf8("cbSpeed"));
        sizePolicy.setHeightForWidth(cbSpeed->sizePolicy().hasHeightForWidth());
        cbSpeed->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(cbSpeed);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        openButton = new QPushButton(groupBox);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openButton->sizePolicy().hasHeightForWidth());
        openButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(openButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);

        gridLayout_3->addWidget(tabWidget, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 20));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_File->setEnabled(true);
        menu_Settings = new QMenu(menuBar);
        menu_Settings->setObjectName(QString::fromUtf8("menu_Settings"));
        menu_Settings->setSeparatorsCollapsible(false);
        menuCheck = new QMenu(menuBar);
        menuCheck->setObjectName(QString::fromUtf8("menuCheck"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(24, 24));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Settings->menuAction());
        menuBar->addAction(menuCheck->menuAction());
        menu_File->addAction(actionClearConsole);
        menu_File->addAction(actionQuit);
        menu_Settings->addAction(actionTimeouts);
        menu_Settings->addAction(actionColor_palette);
        mainToolBar->addAction(actionClearConsole);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(tabWidget, SIGNAL(currentChanged(int)), MainWindow, SLOT(on_changeTab()));

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionClearConsole->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionClearConsole->setToolTip(QApplication::translate("MainWindow", "Press to clear console window", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionQuit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionQuit->setToolTip(QApplication::translate("MainWindow", "Quit program", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionTimeouts->setText(QApplication::translate("MainWindow", "Edit timeouts", 0, QApplication::UnicodeUTF8));
        actionColor_palette->setText(QApplication::translate("MainWindow", "Color palette", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Serial port settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">Serial port:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        cbPort->clear();
        cbPort->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "COM1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "COM2", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">Baude rate:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        cbSpeed->clear();
        cbSpeed->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1:9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2:19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "3:38400", 0, QApplication::UnicodeUTF8)
        );
        openButton->setText(QApplication::translate("MainWindow", "Open port", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Settings->setTitle(QApplication::translate("MainWindow", "&Settings", 0, QApplication::UnicodeUTF8));
        menuCheck->setTitle(QApplication::translate("MainWindow", "Check", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

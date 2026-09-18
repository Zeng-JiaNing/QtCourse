/********************************************************************************
** Form generated from reading UI file 'qwmainwind.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QWMAINWIND_H
#define UI_QWMAINWIND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QWMainWind
{
public:
    QAction *actCut;
    QAction *actCopy;
    QAction *actPaste;
    QAction *actFontBold;
    QAction *actFontItalic;
    QAction *actFontUnder;
    QAction *actClose;
    QAction *actOpen;
    QAction *actClear;
    QAction *actFont;
    QAction *actAbout;
    QAction *actNew;
    QAction *actToolbarLab;
    QWidget *centralWidget;
    QTextEdit *txtEdit;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QWMainWind)
    {
        if (QWMainWind->objectName().isEmpty())
            QWMainWind->setObjectName(QString::fromUtf8("QWMainWind"));
        QWMainWind->resize(543, 258);
        QFont font;
        font.setPointSize(11);
        QWMainWind->setFont(font);
        actCut = new QAction(QWMainWind);
        actCut->setObjectName(QString::fromUtf8("actCut"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/cut.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actCut->setIcon(icon);
        actCopy = new QAction(QWMainWind);
        actCopy->setObjectName(QString::fromUtf8("actCopy"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/120.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actCopy->setIcon(icon1);
        actPaste = new QAction(QWMainWind);
        actPaste->setObjectName(QString::fromUtf8("actPaste"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/paste.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actPaste->setIcon(icon2);
        actFontBold = new QAction(QWMainWind);
        actFontBold->setObjectName(QString::fromUtf8("actFontBold"));
        actFontBold->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/BLD.BMP"), QSize(), QIcon::Normal, QIcon::Off);
        actFontBold->setIcon(icon3);
        actFontItalic = new QAction(QWMainWind);
        actFontItalic->setObjectName(QString::fromUtf8("actFontItalic"));
        actFontItalic->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/images/ITL.BMP"), QSize(), QIcon::Normal, QIcon::Off);
        actFontItalic->setIcon(icon4);
        actFontUnder = new QAction(QWMainWind);
        actFontUnder->setObjectName(QString::fromUtf8("actFontUnder"));
        actFontUnder->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/images/WORDUNDR.BMP"), QSize(), QIcon::Normal, QIcon::Off);
        actFontUnder->setIcon(icon5);
        actClose = new QAction(QWMainWind);
        actClose->setObjectName(QString::fromUtf8("actClose"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/images/exit.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actClose->setIcon(icon6);
        actOpen = new QAction(QWMainWind);
        actOpen->setObjectName(QString::fromUtf8("actOpen"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/images/open3.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actOpen->setIcon(icon7);
        actClear = new QAction(QWMainWind);
        actClear->setObjectName(QString::fromUtf8("actClear"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/images/103.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actClear->setIcon(icon8);
        actFont = new QAction(QWMainWind);
        actFont->setObjectName(QString::fromUtf8("actFont"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/images/20.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actFont->setIcon(icon9);
        actAbout = new QAction(QWMainWind);
        actAbout->setObjectName(QString::fromUtf8("actAbout"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/images/about.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actAbout->setIcon(icon10);
        actNew = new QAction(QWMainWind);
        actNew->setObjectName(QString::fromUtf8("actNew"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/images/new2.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actNew->setIcon(icon11);
        actToolbarLab = new QAction(QWMainWind);
        actToolbarLab->setObjectName(QString::fromUtf8("actToolbarLab"));
        actToolbarLab->setCheckable(true);
        actToolbarLab->setChecked(true);
        actToolbarLab->setMenuRole(QAction::TextHeuristicRole);
        centralWidget = new QWidget(QWMainWind);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        txtEdit = new QTextEdit(centralWidget);
        txtEdit->setObjectName(QString::fromUtf8("txtEdit"));
        txtEdit->setGeometry(QRect(50, 15, 396, 136));
        QFont font1;
        font1.setPointSize(16);
        txtEdit->setFont(font1);
        QWMainWind->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QWMainWind);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 543, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        QWMainWind->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QWMainWind);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        QWMainWind->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QWMainWind);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QWMainWind->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(actNew);
        menu->addAction(actOpen);
        menu->addSeparator();
        menu->addAction(actClose);
        menu_2->addAction(actCut);
        menu_2->addAction(actCopy);
        menu_2->addAction(actPaste);
        menu_2->addSeparator();
        menu_2->addAction(actClear);
        menu_3->addAction(actFontBold);
        menu_3->addAction(actFontItalic);
        menu_3->addAction(actFontUnder);
        menu_3->addSeparator();
        menu_3->addAction(actToolbarLab);
        menu_4->addAction(actAbout);
        mainToolBar->addAction(actNew);
        mainToolBar->addAction(actAbout);
        mainToolBar->addAction(actOpen);
        mainToolBar->addAction(actClear);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actCut);
        mainToolBar->addAction(actCopy);
        mainToolBar->addAction(actPaste);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actFontItalic);
        mainToolBar->addAction(actFontBold);
        mainToolBar->addAction(actFontUnder);
        mainToolBar->addSeparator();

        retranslateUi(QWMainWind);
        QObject::connect(actClose, SIGNAL(triggered()), QWMainWind, SLOT(close()));
        QObject::connect(actClear, SIGNAL(triggered()), txtEdit, SLOT(clear()));
        QObject::connect(actCut, SIGNAL(triggered()), txtEdit, SLOT(cut()));
        QObject::connect(actCopy, SIGNAL(triggered()), txtEdit, SLOT(copy()));
        QObject::connect(actPaste, SIGNAL(triggered()), txtEdit, SLOT(paste()));

        QMetaObject::connectSlotsByName(QWMainWind);
    } // setupUi

    void retranslateUi(QMainWindow *QWMainWind)
    {
        QWMainWind->setWindowTitle(QApplication::translate("QWMainWind", "QWMainWind", nullptr));
        actCut->setText(QApplication::translate("QWMainWind", "\345\211\252\345\210\207", nullptr));
#ifndef QT_NO_TOOLTIP
        actCut->setToolTip(QApplication::translate("QWMainWind", "\345\211\252\345\210\207", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actCut->setShortcut(QApplication::translate("QWMainWind", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
        actCopy->setText(QApplication::translate("QWMainWind", "\345\244\215\345\210\266", nullptr));
#ifndef QT_NO_TOOLTIP
        actCopy->setToolTip(QApplication::translate("QWMainWind", "\345\244\215\345\210\266", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actCopy->setShortcut(QApplication::translate("QWMainWind", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        actPaste->setText(QApplication::translate("QWMainWind", "\347\262\230\350\264\264", nullptr));
#ifndef QT_NO_TOOLTIP
        actPaste->setToolTip(QApplication::translate("QWMainWind", "\347\262\230\350\264\264", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actPaste->setShortcut(QApplication::translate("QWMainWind", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
        actFontBold->setText(QApplication::translate("QWMainWind", "\347\262\227\344\275\223", nullptr));
#ifndef QT_NO_TOOLTIP
        actFontBold->setToolTip(QApplication::translate("QWMainWind", "\347\262\227\344\275\223", nullptr));
#endif // QT_NO_TOOLTIP
        actFontItalic->setText(QApplication::translate("QWMainWind", "\346\226\234\344\275\223", nullptr));
#ifndef QT_NO_TOOLTIP
        actFontItalic->setToolTip(QApplication::translate("QWMainWind", "\346\226\234\344\275\223", nullptr));
#endif // QT_NO_TOOLTIP
        actFontUnder->setText(QApplication::translate("QWMainWind", "\344\270\213\345\210\222\347\272\277", nullptr));
#ifndef QT_NO_TOOLTIP
        actFontUnder->setToolTip(QApplication::translate("QWMainWind", "\344\270\213\345\210\222\347\272\277", nullptr));
#endif // QT_NO_TOOLTIP
        actClose->setText(QApplication::translate("QWMainWind", "\351\200\200\345\207\272", nullptr));
#ifndef QT_NO_TOOLTIP
        actClose->setToolTip(QApplication::translate("QWMainWind", "\351\200\200\345\207\272", nullptr));
#endif // QT_NO_TOOLTIP
        actOpen->setText(QApplication::translate("QWMainWind", "\346\211\223\345\274\200...", nullptr));
#ifndef QT_NO_TOOLTIP
        actOpen->setToolTip(QApplication::translate("QWMainWind", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actOpen->setShortcut(QApplication::translate("QWMainWind", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actClear->setText(QApplication::translate("QWMainWind", "\346\270\205\347\251\272", nullptr));
#ifndef QT_NO_TOOLTIP
        actClear->setToolTip(QApplication::translate("QWMainWind", "\346\270\205\347\251\272\345\206\205\345\256\271", nullptr));
#endif // QT_NO_TOOLTIP
        actFont->setText(QApplication::translate("QWMainWind", "\345\255\227\344\275\223...", nullptr));
#ifndef QT_NO_TOOLTIP
        actFont->setToolTip(QApplication::translate("QWMainWind", "\345\255\227\344\275\223\350\256\276\347\275\256", nullptr));
#endif // QT_NO_TOOLTIP
        actAbout->setText(QApplication::translate("QWMainWind", "\345\205\263\344\272\216", nullptr));
#ifndef QT_NO_TOOLTIP
        actAbout->setToolTip(QApplication::translate("QWMainWind", "\345\205\263\344\272\216", nullptr));
#endif // QT_NO_TOOLTIP
        actNew->setText(QApplication::translate("QWMainWind", "\346\226\260\345\273\272", nullptr));
#ifndef QT_NO_SHORTCUT
        actNew->setShortcut(QApplication::translate("QWMainWind", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actToolbarLab->setText(QApplication::translate("QWMainWind", "\346\230\276\347\244\272\345\267\245\345\205\267\346\240\217\346\226\207\345\255\227\346\240\207\347\255\276", nullptr));
        menu->setTitle(QApplication::translate("QWMainWind", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("QWMainWind", "\347\274\226\350\276\221", nullptr));
        menu_3->setTitle(QApplication::translate("QWMainWind", "\346\240\274\345\274\217", nullptr));
        menu_4->setTitle(QApplication::translate("QWMainWind", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QWMainWind: public Ui_QWMainWind {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QWMAINWIND_H

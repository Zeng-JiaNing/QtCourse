#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载Qt自带的中文翻译：QMessageBox的"保存/放弃/取消"、对话框按钮显示中文
    QTranslator translator;
    translator.load("qtbase_zh_CN.qm",
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}

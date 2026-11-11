#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "finddialog.h"
#include "replacedialog.h"
#include <QLabel>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 字号选择框不是QAction，Action编辑器放不进工具栏，用代码插到"字体颜色"左边
    QWidget *fontWidget = new QWidget(this);
    QHBoxLayout *fontLayout = new QHBoxLayout(fontWidget);
    fontLayout->setContentsMargins(4, 0, 4, 0);
    fontLayout->setSpacing(4);
    fontLayout->addWidget(new QLabel(QStringLiteral("字号"), fontWidget));
    fontSizeSpinBox = new QSpinBox(fontWidget);
    fontSizeSpinBox->setRange(6, 72);
    fontSizeSpinBox->setValue(12);
    fontLayout->addWidget(fontSizeSpinBox);
    ui->toolBar->insertWidget(ui->actionFontColor, fontWidget);

    // 三个对话框的菜单入口
    connect(ui->actionAbout,   &QAction::triggered, this, &MainWindow::showAbout);
    connect(ui->actionFind,    &QAction::triggered, this, &MainWindow::showFind);
    connect(ui->actionReplace, &QAction::triggered, this, &MainWindow::showReplace);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 关于：模态打开，点确定才能回主窗口
void MainWindow::showAbout()
{
    AboutDialog dlg(this);
    dlg.exec();
}

// 查找/替换：无模式打开，不关掉也能继续编辑主窗口
// 对话框发出的 findNext 等信号在"处理查找/替换窗口操作"步骤接上
void MainWindow::showFind()
{
    if (!findDialog)
        findDialog = new FindDialog(this);
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::showReplace()
{
    if (!replaceDialog)
        replaceDialog = new ReplaceDialog(this);
    replaceDialog->show();
    replaceDialog->raise();
    replaceDialog->activateWindow();
}

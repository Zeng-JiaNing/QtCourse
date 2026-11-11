#include "mainwindow.h"
#include "ui_mainwindow.h"
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

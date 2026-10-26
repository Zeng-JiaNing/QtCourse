#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 统一建立按键与处理函数的连接
// 数字键用循环+lambda连接，其余按键逐个连接到对应槽函数
void MainWindow::connectButtons()
{
    const QList<QPushButton *> digitButtons = {
        ui->btn0, ui->btn1, ui->btn2, ui->btn3, ui->btn4,
        ui->btn5, ui->btn6, ui->btn7, ui->btn8, ui->btn9
    };
    for (QPushButton *btn : digitButtons) {
        connect(btn, &QPushButton::clicked, this, [this, btn] { inputDigit(btn->text()); });
    }

    connect(ui->btnDot,        &QPushButton::clicked, this, &MainWindow::pointClicked);
    connect(ui->btnSign,       &QPushButton::clicked, this, &MainWindow::signClicked);
    connect(ui->btnBack,       &QPushButton::clicked, this, &MainWindow::backspaceClicked);
    connect(ui->btnClearEntry, &QPushButton::clicked, this, &MainWindow::clearEntryClicked);
    connect(ui->btnClear,      &QPushButton::clicked, this, &MainWindow::clearClicked);
}

// 输入一位数字：新输入状态下直接替换显示，否则追加到末尾
void MainWindow::inputDigit(const QString &digit)
{
    if (m_waitingForOperand) {
        ui->display->setText(digit);
        m_waitingForOperand = false;
    } else if (ui->display->text() == "0") {
        ui->display->setText(digit);   // 避免出现 05 这种前导零
    } else {
        ui->display->setText(ui->display->text() + digit);
    }
}

// 输入小数点：新输入状态下自动补前导 0
void MainWindow::inputPoint()
{
    if (m_waitingForOperand) {
        ui->display->setText("0.");
        m_waitingForOperand = false;
    } else {
        ui->display->setText(ui->display->text() + ".");
    }
}

void MainWindow::pointClicked()
{
    inputPoint();
}

// 正负号：翻转当前输入的符号，0 不参与翻转
void MainWindow::signClicked()
{
    QString text = ui->display->text();
    if (text.startsWith('-')) {
        text.remove(0, 1);
    } else if (text != "0") {
        text.prepend('-');
    }
    ui->display->setText(text);
}

// 退格：去掉最后一个字符；删空后回到 0
void MainWindow::backspaceClicked()
{
    if (m_waitingForOperand)
        return;

    QString text = ui->display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        m_waitingForOperand = true;
    }
    ui->display->setText(text);
}

// CE：只清除当前输入的数
void MainWindow::clearEntryClicked()
{
    ui->display->setText("0");
    m_waitingForOperand = true;
}

// C：清除全部状态，回到初始界面
void MainWindow::clearClicked()
{
    ui->display->setText("0");
    m_waitingForOperand = true;
}

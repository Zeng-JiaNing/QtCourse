#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectButtons();

    // 按键一律不接收焦点：避免鼠标点击某个按键后它抢走焦点，
    // 导致回车/空格键重复触发该按钮而不是走全局键盘处理
    for (QPushButton *btn : findChildren<QPushButton *>())
        btn->setFocusPolicy(Qt::NoFocus);
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

    // 四个运算符按键共用 operatorClicked，靠按键文本区分
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnSub, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnMul, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnDiv, &QPushButton::clicked, this, &MainWindow::operatorClicked);

    connect(ui->btnEq,  &QPushButton::clicked, this, &MainWindow::equalsClicked);
}

// 输入一位数字：刚算完结果则新开一轮，否则替换/追加显示
void MainWindow::inputDigit(const QString &digit)
{
    if (m_justCalculated) {
        // 计算完成后直接输入数字：丢弃结果，开始新一轮输入
        m_expression.clear();
        ui->expressionLabel->setText(m_expression);
        ui->display->setText(digit);
        m_waitingForOperand = false;
        m_justCalculated = false;
        return;
    }

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
    if (m_justCalculated) {
        m_expression.clear();
        ui->expressionLabel->setText(m_expression);
        m_justCalculated = false;
        m_waitingForOperand = true;    // 计算完成后输入小数点：按新输入处理
    }

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

// CE：只清除当前输入的数，不影响已登记的运算
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
    m_justCalculated = false;
    m_pendingOperand = 0.0;
    m_pendingOperator.clear();
    m_expression.clear();
    ui->expressionLabel->setText(m_expression);
}

// 处理运算符：若有待运算则先算出中间结果，再登记新的运算
// 采用"即时运算"策略：2+3×4 = 20（从左到右逐级计算，与 Windows 标准计算器一致）
void MainWindow::applyOperator(const QString &op)
{
    if (m_justCalculated) {
        m_expression.clear();          // 等号后直接按运算符：以结果为新表达式的起点
        m_justCalculated = false;
    }

    double current = ui->display->text().toDouble();

    if (!m_pendingOperator.isEmpty()) {
        m_pendingOperand = calculate(m_pendingOperand, current, m_pendingOperator);
        ui->display->setText(QString::number(m_pendingOperand, 'g', 12));
        m_expression += QString::number(current, 'g', 12) + ' ';
    } else {
        m_pendingOperand = current;
    }

    m_expression += op + ' ';          // 运算符同步显示到表达式预览行
    ui->expressionLabel->setText(m_expression);

    m_pendingOperator = op;
    m_waitingForOperand = true;
}

void MainWindow::operatorClicked()
{
    applyOperator(static_cast<QPushButton *>(sender())->text());
}

// 等号：执行待运算并显示结果
void MainWindow::equalsClicked()
{
    if (m_pendingOperator.isEmpty() || m_waitingForOperand)
        return;    // 没有完整表达式（只有操作数+操作符）时不响应

    double current = ui->display->text().toDouble();
    double result = calculate(m_pendingOperand, current, m_pendingOperator);

    m_expression += QString::number(current, 'g', 12) + " =";
    ui->expressionLabel->setText(m_expression);

    ui->display->setText(QString::number(result, 'g', 12));
    m_pendingOperand = result;
    m_pendingOperator.clear();
    m_waitingForOperand = true;
    m_justCalculated = true;
}

// 执行一次四则运算
double MainWindow::calculate(double a, double b, const QString &op)
{
    if (op == "+") return a + b;
    if (op == "−") return a - b;
    if (op == "×") return a * b;
    if (op == "÷") return a / b;
    return 0.0;
}

// 键盘输入入口：所有按键都映射到与鼠标按键相同的处理函数，
// 保证鼠标输入与键盘输入复用同一套逻辑、行为完全一致
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if (key >= Qt::Key_0 && key <= Qt::Key_9) {
        inputDigit(QString::number(key - Qt::Key_0));
        return;
    }

    switch (key) {
    case Qt::Key_Period:
    case Qt::Key_Comma:     inputPoint();        break;   // 小数点（兼容部分键盘的逗号）
    case Qt::Key_Plus:      applyOperator("+");  break;
    case Qt::Key_Minus:     applyOperator("−");  break;   // 与按钮文本一致的 Unicode 减号
    case Qt::Key_Asterisk:  applyOperator("×");  break;
    case Qt::Key_Slash:     applyOperator("÷");  break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Equal:     equalsClicked();     break;
    case Qt::Key_Backspace: backspaceClicked();  break;
    case Qt::Key_Delete:    clearEntryClicked(); break;   // Delete = CE
    case Qt::Key_Escape:    clearClicked();      break;   // Esc   = C
    case Qt::Key_F9:        signClicked();       break;   // F9    = ±（与Windows计算器一致）
    default:
        QMainWindow::keyPressEvent(event);
    }
}

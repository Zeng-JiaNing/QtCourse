#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void pointClicked();        // 小数点
    void signClicked();         // 正负号 ±
    void backspaceClicked();    // 退格
    void clearEntryClicked();   // 清除当前输入 CE
    void clearClicked();        // 全部清除 C
    void operatorClicked();     // 四则运算符（从按键文本取操作符）
    void equalsClicked();       // 等号

private:
    void connectButtons();                  // 建立所有按键的信号连接
    void inputDigit(const QString &digit);  // 输入一位数字
    void inputPoint();                      // 输入小数点
    void applyOperator(const QString &op);  // 处理运算符：保存操作数并登记待运算
    double calculate(double a, double b, const QString &op);  // 执行一次四则运算

    Ui::MainWindow *ui;
    bool m_waitingForOperand = true;   // true：下一次数字输入替换显示（开始新操作数）
    bool m_justCalculated = false;     // true：刚按过等号，用于决定后续输入是新开还是延续
    double m_pendingOperand = 0.0;     // 第一个操作数（等待与显示中的数进行运算）
    QString m_pendingOperator;         // 待执行的操作符，空串表示当前没有待运算
    QString m_expression;              // 表达式预览内容（显示在 expressionLabel 上）
};
#endif // MAINWINDOW_H

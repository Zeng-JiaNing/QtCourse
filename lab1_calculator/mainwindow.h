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

private:
    void connectButtons();                  // 建立所有按键的信号连接
    void inputDigit(const QString &digit);  // 输入一位数字
    void inputPoint();                      // 输入小数点

    Ui::MainWindow *ui;
    bool m_waitingForOperand = true;  // true：下一次数字输入替换显示（开始新操作数）
};
#endif // MAINWINDOW_H

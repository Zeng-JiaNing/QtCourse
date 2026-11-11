#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FindDialog;
class ReplaceDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showAbout();      // 关于对话框（模态）
    void showFind();       // 查找对话框（无模式）
    void showReplace();    // 替换对话框（无模式）

private:
    Ui::MainWindow *ui;
    QSpinBox *fontSizeSpinBox = nullptr;   // 工具栏上的字号选择框（非Action，代码里插入）

    FindDialog *findDialog = nullptr;      // 无模式对话框只创建一次，重复点菜单只是调到前台
    ReplaceDialog *replaceDialog = nullptr;
};

#endif // MAINWINDOW_H

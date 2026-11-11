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

protected:
    void closeEvent(QCloseEvent *event) override;   // 关窗前询问是否保存

private slots:
    void showAbout();      // 关于对话框（模态）
    void showFind();       // 查找对话框（无模式）
    void showReplace();    // 替换对话框（无模式）

    void newFile();        // 新建
    void openFile();       // 打开
    bool saveFile();       // 保存（未命名自动转另存为），返回是否保存成功
    bool saveFileAs();     // 另存为
    void updateTitle(bool modified);   // 标题跟随"文件名+修改状态"变化
    void updatePasteEnabled();         // 剪贴板里有文本时粘贴键才可用

private:
    bool maybeSave();                       // 有未保存修改时询问，点取消返回false
    bool loadFile(const QString &path);     // 读文件进编辑器
    bool writeToFile(const QString &path);  // 把编辑器内容写盘

    Ui::MainWindow *ui;
    QSpinBox *fontSizeSpinBox = nullptr;   // 工具栏上的字号选择框（非Action，代码里插入）

    FindDialog *findDialog = nullptr;      // 无模式对话框只创建一次，重复点菜单只是调到前台
    ReplaceDialog *replaceDialog = nullptr;

    QString m_currentFile;                 // 当前文件路径；空 = 未命名
};

#endif // MAINWINDOW_H

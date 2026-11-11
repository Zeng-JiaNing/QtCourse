#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class FindDialog; }
QT_END_NAMESPACE

// 查找对话框：无模式窗口，不关掉也能回到主窗口继续编辑
// 对话框只负责收集查找条件，发信号给主窗口执行查找
class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();

signals:
    // 点"查找下一个"时发出；backward=true 表示向上找
    void findNext(const QString &text, bool caseSensitive, bool backward);

private slots:
    void onFindNext();

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H

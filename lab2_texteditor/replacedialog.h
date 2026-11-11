#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ReplaceDialog; }
QT_END_NAMESPACE

// 替换对话框：无模式窗口，只收集条件发信号，替换逻辑在主窗口
class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr);
    ~ReplaceDialog();

signals:
    void findNext(const QString &text, bool caseSensitive);
    void replaceOne(const QString &text, const QString &to, bool caseSensitive);
    void replaceAll(const QString &text, const QString &to, bool caseSensitive);

private slots:
    void onFindNext();
    void onReplace();
    void onReplaceAll();

private:
    Ui::ReplaceDialog *ui;
};

#endif // REPLACEDIALOG_H

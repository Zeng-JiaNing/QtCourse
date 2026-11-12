#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

class QPaintEvent;
class QResizeEvent;

// 带行号区的编辑器：从QPlainTextEdit派生（Qt官方CodeEditor示例改法）。
// 行号区是一个贴在编辑框左侧的QWidget，自己不排文本，只负责画数字；
// 滚动/增删行时通过信号让主类把整块区域重画
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = nullptr);

    void setLineNumbersVisible(bool visible);   // 视图菜单"行号"开关
    void lineNumberAreaPaintEvent(QPaintEvent *event);   // 行号区重画（由LineNumberArea回调）
    int lineNumberAreaWidth();                  // 行号区该多宽：按最大行数的位数算

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);   // 行数变了→行号区宽度变了
    void updateLineNumberArea(const QRect &rect, int dy);// 滚动/内容变了→行号区重画
    void highlightCurrentLine();                         // 当前行高亮

private:
    QWidget *lineNumberArea = nullptr;
    bool lineNumbersVisible = true;
};

#endif // CODEEDITOR_H

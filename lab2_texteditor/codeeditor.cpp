#include "codeeditor.h"
#include <QPainter>
#include <QTextBlock>
#include <QTextEdit>

// 行号区控件：不自己存内容，画事件整个转交给CodeEditor处理。
// 定义在.cpp里是因为要调用CodeEditor的方法，必须等CodeEditor定义完
class LineNumberArea : public QWidget
{
public:
    explicit LineNumberArea(CodeEditor *editor)
        : QWidget(editor), codeEditor(editor) {}

    // 布局系统问行号区该多宽时，按编辑器算出的宽度回答
    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    // 行数变化（回车/删行）→ 重算行号区宽度；滚动或改动 → 重画行号区；
    // 光标移动 → 当前行高亮
    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest,     this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

// 行号区宽度 = 左右边距3px + 最大行号位数×一个数字的宽度。
// 例如999行就是3位，行数超过9就自动变宽，不会出现两位数挤在一位宽度里
int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return space;
}

// 显示/隐藏行号：藏起来时把预留的左边距也收回来，正文占满整个窗口
void CodeEditor::setLineNumbersVisible(bool visible)
{
    lineNumbersVisible = visible;
    lineNumberArea->setVisible(visible);
    setViewportMargins(visible ? lineNumberAreaWidth() : 0, 0, 0, 0);
}

// 行号区的画法：浅灰底，从第一个可见块往下逐块画行号（块号+1）
// 一个块=一个逻辑行，长行自动折行后也只显示一个号
void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(240, 240, 240));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            painter.setPen(Qt::darkGray);
            painter.drawText(0, top, lineNumberArea->width() - 3,
                             fontMetrics().height(),
                             Qt::AlignRight, QString::number(blockNumber + 1));
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void CodeEditor::updateLineNumberAreaWidth(int /*newBlockCount*/)
{
    setViewportMargins(lineNumbersVisible ? lineNumberAreaWidth() : 0, 0, 0, 0);
}

// 编辑器内容滚动/变化时把行号区跟着挪：滚动了dy像素就平移，否则重画变化的那一小条
void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(),
                                      lineNumberAreaWidth(), cr.height()));
}

// 当前行高亮：用FullWidthSelection的ExtraSelection整行铺淡黄色，
// 光标一动就重设一遍（不动文本本身，只是显示层）
void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(QColor(Qt::yellow).lighter(160));
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

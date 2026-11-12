#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "finddialog.h"
#include "replacedialog.h"
#include "codeeditor.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QCloseEvent>
#include <QTextDocument>
#include <QPlainTextEdit>
#include <QClipboard>
#include <QGuiApplication>
#include <QColorDialog>
#include <QFont>
#include <QPalette>
#include <QStatusBar>
#include <QTextCursor>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 字号选择框不是QAction，Action编辑器放不进工具栏，用代码插到"字体颜色"左边
    QWidget *fontWidget = new QWidget(this);
    QHBoxLayout *fontLayout = new QHBoxLayout(fontWidget);
    fontLayout->setContentsMargins(4, 0, 4, 0);
    fontLayout->setSpacing(4);
    fontLayout->addWidget(new QLabel(QStringLiteral("字号"), fontWidget));
    fontSizeSpinBox = new QSpinBox(fontWidget);
    fontSizeSpinBox->setRange(6, 72);
    fontSizeSpinBox->setValue(12);
    fontLayout->addWidget(fontSizeSpinBox);
    ui->toolBar->insertWidget(ui->actionFontColor, fontWidget);

    // 三个对话框的菜单入口
    connect(ui->actionAbout,   &QAction::triggered, this, &MainWindow::showAbout);
    connect(ui->actionFind,    &QAction::triggered, this, &MainWindow::showFind);
    connect(ui->actionReplace, &QAction::triggered, this, &MainWindow::showReplace);

    // 文件操作
    connect(ui->actionNew,    &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpen,   &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave,   &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(ui->actionExit,   &QAction::triggered, this, &MainWindow::close);   // 退出也走关闭询问

    // 文档的修改状态一变（改一个字变true / 存盘变false），标题上的*就跟着变
    connect(ui->textEdit->document(), &QTextDocument::modificationChanged,
            this, &MainWindow::updateTitle);

    // ==================== 编辑操作 ====================
    // 六个编辑Action直接接到编辑框的现成槽上，不另写处理函数
    connect(ui->actionUndo,      &QAction::triggered, ui->textEdit, &QPlainTextEdit::undo);
    connect(ui->actionRedo,      &QAction::triggered, ui->textEdit, &QPlainTextEdit::redo);
    connect(ui->actionCut,       &QAction::triggered, ui->textEdit, &QPlainTextEdit::cut);
    connect(ui->actionCopy,      &QAction::triggered, ui->textEdit, &QPlainTextEdit::copy);
    connect(ui->actionPaste,     &QAction::triggered, ui->textEdit, &QPlainTextEdit::paste);
    connect(ui->actionSelectAll, &QAction::triggered, ui->textEdit, &QPlainTextEdit::selectAll);

    // ==================== Action使能 ====================
    // 文档的撤销栈有没有东西 → 撤销/重做键亮或灰（信号直连QAction::setEnabled）
    connect(ui->textEdit->document(), &QTextDocument::undoAvailable,
            ui->actionUndo, &QAction::setEnabled);
    connect(ui->textEdit->document(), &QTextDocument::redoAvailable,
            ui->actionRedo, &QAction::setEnabled);
    // 编辑框里有没有选中内容 → 剪切/复制键亮或灰
    connect(ui->textEdit, &QPlainTextEdit::copyAvailable,
            ui->actionCopy, &QAction::setEnabled);
    connect(ui->textEdit, &QPlainTextEdit::copyAvailable,
            ui->actionCut, &QAction::setEnabled);
    // 系统剪贴板内容一变（含从别的程序复制）→ 粘贴键跟着亮或灰
    connect(QGuiApplication::clipboard(), &QClipboard::dataChanged,
            this, &MainWindow::updatePasteEnabled);

    // 初始状态：没有任何可撤销/重做的内容，也没选中，先全部灰着等信号点亮
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    updatePasteEnabled();       // 粘贴不看文档看剪贴板，启动时按剪贴板实况定

    // ==================== 格式设置 ====================
    // 字号框初始值同步成编辑器当前字号，不然框里写12、文字实际是9pt，对不上
    fontSizeSpinBox->setValue(ui->textEdit->font().pointSize());
    // valueChanged有int/QString两个重载，static_cast指明取int那个
    connect(fontSizeSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::changeFontSize);
    connect(ui->actionFontColor, &QAction::triggered,     this, &MainWindow::changeFontColor);
    connect(ui->actionBgColor,   &QAction::triggered,     this, &MainWindow::changeBgColor);
    connect(ui->actionWrap,      &QAction::toggled,       this, &MainWindow::toggleWrap);

    // ==================== 视图与状态栏 ====================
    // 视图菜单的两个勾选项直接开关工具栏/状态栏，勾没了工具栏就藏起来
    connect(ui->actionToolbar,   &QAction::toggled, ui->toolBar,   &QToolBar::setVisible);
    connect(ui->actionStatusbar, &QAction::toggled, ui->statusbar, &QStatusBar::setVisible);

    // 状态栏布局：左边跟文件路径，右边固定放行列位置
    statusPathLabel = new QLabel(this);
    statusPosLabel  = new QLabel(this);
    ui->statusbar->addWidget(statusPathLabel);           // 左侧，可有可无型信息
    ui->statusbar->addPermanentWidget(statusPosLabel);   // 右侧，不会被临时消息挤走
    // 光标一动（打字、删除、点鼠标都算）就刷新行列
    connect(ui->textEdit, &QPlainTextEdit::cursorPositionChanged,
            this, &MainWindow::updateCursorPosition);

    // ==================== 行号 ====================
    // textEdit在Designer里promote成了CodeEditor（自带行号区），
    // 主窗口只管"行号"菜单这个显示开关；启动时按勾选状态对齐（默认不显示）
    connect(ui->actionLineNumbers, &QAction::toggled,
            ui->textEdit, &CodeEditor::setLineNumbersVisible);
    ui->textEdit->setLineNumbersVisible(ui->actionLineNumbers->isChecked());

    // 启动时把标题和状态栏摆好；放在这里是因为updateTitle会刷状态栏路径，
    // 必须等两个Label建出来之后才能调
    updateTitle(ui->textEdit->document()->isModified());
    updateCursorPosition();
}

// 剪贴板里有文本才允许粘贴；从别的程序复制了东西，这里的粘贴键也会自己亮起来
void MainWindow::updatePasteEnabled()
{
    ui->actionPaste->setEnabled(!QGuiApplication::clipboard()->text().isEmpty());
}

// ==================== 格式设置 ====================

// 字号选择框一转，编辑区字号跟着变：QPlainTextEdit用控件字体渲染全部文本，
// 改一处就全变（不像QTextEdit要按选区设字符格式）
void MainWindow::changeFontSize(int size)
{
    QFont font = ui->textEdit->font();
    font.setPointSize(size);
    ui->textEdit->setFont(font);
}

// 字体颜色：改编辑框调色板的 Text 色；取色器默认给当前文字颜色，取消则不动
void MainWindow::changeFontColor()
{
    QColor color = QColorDialog::getColor(ui->textEdit->palette().color(QPalette::Text),
                                          this, QStringLiteral("选择字体颜色"));
    if (!color.isValid())
        return;                 // 用户点了取消，返回的是非法颜色
    QPalette pal = ui->textEdit->palette();
    pal.setColor(QPalette::Text, color);
    ui->textEdit->setPalette(pal);
}

// 背景色：改调色板的 Base（文本控件底色）
void MainWindow::changeBgColor()
{
    QColor color = QColorDialog::getColor(ui->textEdit->palette().color(QPalette::Base),
                                          this, QStringLiteral("选择背景颜色"));
    if (!color.isValid())
        return;
    QPalette pal = ui->textEdit->palette();
    pal.setColor(QPalette::Base, color);
    ui->textEdit->setPalette(pal);
}

// 自动换行开关：勾选=到窗口右边缘折行；取消=一行写到头，出横向滚动条
void MainWindow::toggleWrap(bool checked)
{
    ui->textEdit->setLineWrapMode(checked ? QPlainTextEdit::WidgetWidth
                                          : QPlainTextEdit::NoWrap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== 对话框 ====================

// 关于：模态打开，点确定才能回主窗口
void MainWindow::showAbout()
{
    AboutDialog dlg(this);
    dlg.exec();
}

// 查找/替换：无模式打开，不关掉也能继续编辑主窗口
void MainWindow::showFind()
{
    if (!findDialog) {
        findDialog = new FindDialog(this);
        // 对话框只发条件，怎么找由主窗口实现
        connect(findDialog, &FindDialog::findNext, this, &MainWindow::findFromDialog);
    }
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::showReplace()
{
    if (!replaceDialog) {
        replaceDialog = new ReplaceDialog(this);
        // 替换窗口里的"查找下一个"固定向后找（它没有方向选项）
        connect(replaceDialog, &ReplaceDialog::findNext, this,
                [this](const QString &text, bool caseSensitive) {
                    findFromDialog(text, caseSensitive, false);
                });
        connect(replaceDialog, &ReplaceDialog::replaceOne, this, &MainWindow::replaceFromDialog);
        connect(replaceDialog, &ReplaceDialog::replaceAll, this, &MainWindow::replaceAllFromDialog);
    }
    replaceDialog->show();
    replaceDialog->raise();
    replaceDialog->activateWindow();
}

// ==================== 文件操作 ====================

// 新建：当前文档改过就先问一遍，然后清空回"未命名"
void MainWindow::newFile()
{
    if (!maybeSave())
        return;

    ui->textEdit->clear();
    ui->textEdit->document()->setModified(false);
    m_currentFile.clear();
    updateTitle(ui->textEdit->document()->isModified());
}

// 打开：先确认当前内容可以放弃，再读文件
void MainWindow::openFile()
{
    if (!maybeSave())
        return;

    QString path = QFileDialog::getOpenFileName(this, QStringLiteral("打开文件"), QString(),
            QStringLiteral("文本文件 (*.txt *.md *.h *.cpp);;所有文件 (*)"));
    if (path.isEmpty())
        return;                 // 用户取消了选择，什么都不做

    loadFile(path);
}

// 保存：没有路径的（新建未命名）走另存为；有路径的直接写回原文件
bool MainWindow::saveFile()
{
    if (m_currentFile.isEmpty())
        return saveFileAs();
    return writeToFile(m_currentFile);
}

// 另存为：弹对话框选新位置；取消选择不算失败，只是中止操作
bool MainWindow::saveFileAs()
{
    QString path = QFileDialog::getSaveFileName(this, QStringLiteral("另存为"), QString(),
            QStringLiteral("文本文件 (*.txt);;所有文件 (*)"));
    if (path.isEmpty())
        return false;
    return writeToFile(path);
}

// 读文件进编辑器；失败要给看得懂的提示，不能默默失败
bool MainWindow::loadFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, QStringLiteral("小牛文本编辑"),
                QStringLiteral("无法打开文件：\n") + path +
                QStringLiteral("\n错误信息：") + file.errorString());
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    // 异常文件处理：内容里出现 NUL 字节基本就是 exe/图片这类二进制文件，
    // 硬读出来是一屏乱码，不如直接拒绝
    if (data.contains('\0')) {
        QMessageBox::warning(this, QStringLiteral("小牛文本编辑"),
                QStringLiteral("这可能不是文本文件（包含二进制内容），不支持打开。"));
        return false;
    }

    ui->textEdit->setPlainText(QString::fromUtf8(data));
    m_currentFile = path;
    ui->textEdit->document()->setModified(false);
    updateTitle(ui->textEdit->document()->isModified());
    return true;
}

// 真正写盘：写成功才更新当前路径、清掉修改标记（标题的*消失）
bool MainWindow::writeToFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, QStringLiteral("小牛文本编辑"),
                QStringLiteral("无法保存文件：\n") + path +
                QStringLiteral("\n错误信息：") + file.errorString());
        return false;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");      // 统一按UTF-8写，别的编辑器打开不乱码
    out << ui->textEdit->toPlainText();
    file.close();

    m_currentFile = path;
    ui->textEdit->document()->setModified(false);
    updateTitle(ui->textEdit->document()->isModified());
    return true;
}

// 保存/新建/打开/关窗之前的守门员：文档没改过直接放行；
// 改过了弹三选——保存(成功才算通过) / 不保存(放行) / 取消(拦下整个操作)
bool MainWindow::maybeSave()
{
    if (!ui->textEdit->document()->isModified())
        return true;

    QMessageBox::StandardButton choice = QMessageBox::warning(this,
            QStringLiteral("小牛文本编辑"),
            QStringLiteral("当前文件尚未保存，是否保存？"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
            QMessageBox::Save);

    if (choice == QMessageBox::Save)
        return saveFile();                    // 保存失败（如只读）同样拦下
    return choice == QMessageBox::Discard;    // Cancel → false
}

// ==================== 标题与关闭 ====================

// 标题格式：文件名[*] − 小牛文本编辑
// "[*]"是占位符，Qt根据 setWindowModified 的值把它渲染成 * ；未命名时显示"未命名"
void MainWindow::updateTitle(bool modified)
{
    QString name = m_currentFile.isEmpty()
            ? QStringLiteral("未命名")
            : QFileInfo(m_currentFile).fileName();
    setWindowTitle(name + QStringLiteral("[*] - ") + QStringLiteral("小牛文本编辑"));
    setWindowModified(modified);
    updateStatusBarPath();      // 路径和标题同源，m_currentFile一变两个都要刷
}

// ==================== 视图与状态栏 ====================

// 状态栏左侧：当前文件完整路径；未命名就显示"未命名"
void MainWindow::updateStatusBarPath()
{
    statusPathLabel->setText(m_currentFile.isEmpty()
            ? QStringLiteral("未命名")
            : QDir::toNativeSeparators(m_currentFile));
}

// 状态栏右侧：行、列。QPlainTextEdit里"一行"就是一块（block），
// 行号=块号+1，列=块内第几个字符+1，一个汉字算1列
void MainWindow::updateCursorPosition()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    int line = cursor.blockNumber() + 1;
    int col = cursor.positionInBlock() + 1;
    statusPosLabel->setText(QStringLiteral("行 %1，列 %2").arg(line).arg(col));
}

// ==================== 查找与替换 ====================

// 查找对话框"查找下一个"：实际工作交给findInDocument
void MainWindow::findFromDialog(const QString &text, bool caseSensitive, bool backward)
{
    findInDocument(text, caseSensitive, backward);
}

// 查找实现：从光标当前位置起找，找到则选中目标（QPlainTextEdit::find自带选中高亮）；
// 光标后面没有了就绕回文档头（向上找则绕回文档尾）再找一圈——循环查找；
// 整个文档都没有才在状态栏提示"找不到"，不弹窗打断编辑
bool MainWindow::findInDocument(const QString &text, bool caseSensitive, bool backward)
{
    if (text.isEmpty()) {
        ui->statusbar->showMessage(QStringLiteral("查找内容为空"), 2000);
        return false;
    }

    QTextDocument::FindFlags flags;
    if (caseSensitive)
        flags |= QTextDocument::FindCaseSensitively;
    if (backward)
        flags |= QTextDocument::FindBackward;

    if (ui->textEdit->find(text, flags))
        return true;

    QTextCursor restart(ui->textEdit->document());      // 空光标定位到文档头/尾
    restart.movePosition(backward ? QTextCursor::End : QTextCursor::Start);
    ui->textEdit->setTextCursor(restart);

    if (ui->textEdit->find(text, flags))
        return true;

    ui->statusbar->showMessage(QStringLiteral("找不到\"%1\"").arg(text), 2000);
    return false;
}

// 替换对话框"替换"：当前选中的正好是目标就就地换掉（上一轮查找留下的选区）；
// 不是就先找到下一个再换——点一次"替换"等于"查找下一个+换掉"，行为和记事本一致
void MainWindow::replaceFromDialog(const QString &text, const QString &to, bool caseSensitive)
{
    if (text.isEmpty()) {
        ui->statusbar->showMessage(QStringLiteral("查找内容为空"), 2000);
        return;
    }

    Qt::CaseSensitivity cs = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
    QTextCursor cursor = ui->textEdit->textCursor();

    if (cursor.hasSelection() && cursor.selectedText().compare(text, cs) == 0) {
        cursor.insertText(to);                     // 带选区的光标插入文本=替换选区
    } else if (findInDocument(text, caseSensitive, false)) {
        ui->textEdit->textCursor().insertText(to); // find已把目标选中，直接换
    }
}

// 全部替换：从文档开头起，逐个"找到→换掉→从换完的位置继续找"，直到找不到
// 关键点：必须从"换完的位置"继续，不能每换一次就从头找——
// 否则"替换为"里包含查找词（如 a→aa）时会无限循环
void MainWindow::replaceAllFromDialog(const QString &text, const QString &to, bool caseSensitive)
{
    if (text.isEmpty()) {
        ui->statusbar->showMessage(QStringLiteral("查找内容为空"), 2000);
        return;
    }

    QTextDocument::FindFlags flags;
    if (caseSensitive)
        flags |= QTextDocument::FindCaseSensitively;

    int count = 0;
    QTextCursor cursor = ui->textEdit->document()->find(text,
            QTextCursor(ui->textEdit->document()), flags);
    while (!cursor.isNull()) {
        cursor.insertText(to);
        ++count;
        cursor = ui->textEdit->document()->find(text, cursor, flags);
    }

    ui->statusbar->showMessage(QStringLiteral("全部替换完成，共替换 %1 处").arg(count), 3000);
}

// 点窗口右上角的X（以及菜单退出）都会走到这里：没保存完就不许关
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
        event->accept();
    else
        event->ignore();    // 用户点了取消，拦下这次关闭
}

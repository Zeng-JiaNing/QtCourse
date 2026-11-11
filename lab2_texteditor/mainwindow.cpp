#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "finddialog.h"
#include "replacedialog.h"
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

    updateTitle(ui->textEdit->document()->isModified());   // 程序启动时先把标题摆好

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
}

// 剪贴板里有文本才允许粘贴；从别的程序复制了东西，这里的粘贴键也会自己亮起来
void MainWindow::updatePasteEnabled()
{
    ui->actionPaste->setEnabled(!QGuiApplication::clipboard()->text().isEmpty());
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
    if (!findDialog)
        findDialog = new FindDialog(this);
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::showReplace()
{
    if (!replaceDialog)
        replaceDialog = new ReplaceDialog(this);
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
}

// 点窗口右上角的X（以及菜单退出）都会走到这里：没保存完就不许关
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
        event->accept();
    else
        event->ignore();    // 用户点了取消，拦下这次关闭
}

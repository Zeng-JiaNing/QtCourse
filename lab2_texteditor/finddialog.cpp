#include "finddialog.h"
#include "ui_finddialog.h"
#include <QPushButton>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindDialog)
{
    ui->setupUi(this);

    connect(ui->btnFindNext, &QPushButton::clicked, this, &FindDialog::onFindNext);
    connect(ui->btnClose, &QPushButton::clicked, this, &FindDialog::close);
}

FindDialog::~FindDialog()
{
    delete ui;
}

// 只收集条件发信号，不在对话框里碰文本，查找逻辑全在主窗口
void FindDialog::onFindNext()
{
    emit findNext(ui->editFind->text(),
                  ui->checkCase->isChecked(),
                  ui->radioUp->isChecked());
}

#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QPushButton>

ReplaceDialog::ReplaceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);

    connect(ui->btnFindNext, &QPushButton::clicked, this, &ReplaceDialog::onFindNext);
    connect(ui->btnReplace, &QPushButton::clicked, this, &ReplaceDialog::onReplace);
    connect(ui->btnReplaceAll, &QPushButton::clicked, this, &ReplaceDialog::onReplaceAll);
    connect(ui->btnClose, &QPushButton::clicked, this, &ReplaceDialog::close);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::onFindNext()
{
    emit findNext(ui->editFind->text(), ui->checkCase->isChecked());
}

void ReplaceDialog::onReplace()
{
    emit replaceOne(ui->editFind->text(), ui->editReplace->text(), ui->checkCase->isChecked());
}

void ReplaceDialog::onReplaceAll()
{
    emit replaceAll(ui->editFind->text(), ui->editReplace->text(), ui->checkCase->isChecked());
}

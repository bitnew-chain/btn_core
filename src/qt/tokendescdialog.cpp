#include "tokendescdialog.h"
#include "ui_tokendescdialog.h"

#include "tokenfilterproxy.h"
#include "styleSheet.h"

#include <QModelIndex>
#include <QPushButton>

TokenDescDialog::TokenDescDialog(const QModelIndex &idx, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TokenDescDialog)
{
    ui->setupUi(this);
    
    ui->detailText->setStyleSheet("background-color: #FFFFFF; border: none;");
    ui->buttonsContainerWhite->setStyleSheet("background-color: #FFFFFF;");
    ui->buttonBox->button(QDialogButtonBox::Close)->setText(tr("Close"));
    ui->buttonBox->button(QDialogButtonBox::Close)->setStyleSheet("background-color: #4752E8;");
    // Set stylesheet
    SetObjectStyleSheet(this, StyleSheetNames::ScrollBarDark);

    setWindowTitle(tr("Details for %1").arg(idx.data(TokenTransactionTableModel::TxHashRole).toString()));
    QString desc = idx.data(TokenTransactionTableModel::LongDescriptionRole).toString();
    ui->detailText->setHtml(desc);
}

TokenDescDialog::~TokenDescDialog()
{
    delete ui;
}

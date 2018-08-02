#include "titlebar.h"
#include "ui_titlebar.h"
#include "bitcoinunits.h"
#include "optionsmodel.h"
#include "tabbarinfo.h"

#include <QPixmap>
#include <QPalette>
#include "platformstyle.h"

namespace TitleBar_NS {
const int titleHeight = 45;
}
using namespace TitleBar_NS;

TitleBar::TitleBar(const PlatformStyle *platformStyle, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar),
    m_tab(0)
{
    ui->setupUi(this);
    // Set size policy
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->tabWidget->setDrawBase(false);
    ui->tabWidget->setTabsClosable(true);

    ui->tabWidget->setStyleSheet("background-color: #F0F2F8;");
    setFixedHeight(titleHeight);
    ui->lblBalance->setGeometry(220, 1, 180, 38);
    ui->lblBalance->setParent(this);
    m_iconCloseTab = platformStyle->TextColorIcon(":/icons/quit");
}

TitleBar::~TitleBar()
{
    delete ui;
}

void TitleBar::setModel(WalletModel *_model)
{
    this->model = _model;

    setBalance(model->getBalance(), model->getUnconfirmedBalance(), model->getImmatureBalance(),  model->getStake(),
               model->getWatchBalance(), model->getWatchUnconfirmedBalance(), model->getWatchImmatureBalance(), model->getWatchStake());

    connect(model, SIGNAL(balanceChanged(CAmount,CAmount,CAmount,CAmount,CAmount,CAmount,CAmount,CAmount)), this, SLOT(setBalance(CAmount,CAmount,CAmount,CAmount,CAmount,CAmount,CAmount,CAmount)));
}

void TitleBar::setTabBarInfo(QObject *info)
{
    if(m_tab)
    {
        m_tab->detach();
    }

    if(info && info->inherits("TabBarInfo"))
    {
        TabBarInfo* tab = (TabBarInfo*)info;
        m_tab = tab;
        m_tab->attach(ui->tabWidget, &m_iconCloseTab);
    }
}

void TitleBar::setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance, const CAmount& stake,
                                 const CAmount& watchBalance, const CAmount& watchUnconfirmedBalance, const CAmount& watchImmatureBalance, const CAmount& watchStake)
{
    Q_UNUSED(unconfirmedBalance);
    Q_UNUSED(immatureBalance);
    Q_UNUSED(watchBalance);
    Q_UNUSED(stake);
    Q_UNUSED(watchUnconfirmedBalance);
    Q_UNUSED(watchImmatureBalance);
    Q_UNUSED(watchStake);

    if(model && model->getOptionsModel())
    {
        ui->lblBalance->setText(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), balance));
        ui->lblBalance->setStyleSheet("color: #4655EA;");
        ui->lblBalance->setGeometry(220, 1, 180, 38);
        ui->lblBalance->setParent(this);
    }
}

void TitleBar::on_navigationResized(const QSize &_size)
{
    ui->widgetLogo->setFixedWidth(_size.width());
}

void TitleBar::change_lblBalance()
{
    ui->lblBalance->setGeometry(220, 1, 180, 38);
    ui->lblBalance->setParent(this);
}
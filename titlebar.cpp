#include "titlebar.h"
#include <QIcon>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent){
    initControl();
    initConnection();
}

TitleBar::~TitleBar(){
    delete new_btn;
    delete setting_btn;
    delete delete_btn;
    delete close_btn;
    delete titlebar_layout;
}

void TitleBar::initControl(){
    this->setFocusPolicy(Qt::NoFocus);
    new_btn=new QPushButton(this);
    setting_btn=new QPushButton(this);
    delete_btn=new QPushButton(this);
    close_btn=new QPushButton(this);

    new_btn->setStyleSheet("QPushButton{background: transparent;"
                           "width:24px;height:24px;border-image:url(:/Icons/new.png)}"
                           "QPushButton:hover:pressed:{none}");
    setting_btn->setStyleSheet("QPushButton{background: transparent;"
                               "width:24px;height:24px;border-image:url(:/Icons/style.png)}"
                               "QPushButton:hover:pressed:{none}");
    delete_btn->setStyleSheet("QPushButton{background: transparent;"
                              "width:24px;height:24px;border-image:url(:/Icons/delete.png)}"
                              "QPushButton:hover:pressed:{none}");
    close_btn->setStyleSheet("QPushButton{background: transparent;"
                             "width:24px;height:24px;border-image:url(:/Icons/close.png)}"
                             "QPushButton:hover:pressed:{none}");

    titlebar_layout=new QHBoxLayout(this);
    titlebar_layout->addWidget(new_btn);
    titlebar_layout->addWidget(setting_btn);
    titlebar_layout->addStretch();
    titlebar_layout->addWidget(delete_btn);
    titlebar_layout->addStretch();
    titlebar_layout->addSpacing(40);
    titlebar_layout->addWidget(close_btn);

    titlebar_layout->setContentsMargins(6,4,6,0);

    this->setFixedHeight(TITLEBAR_HEIGHT);
}

void TitleBar::initConnection(){
    connect(new_btn,SIGNAL(clicked(bool)),this,SLOT(onNewBtnClicked()));
    connect(setting_btn,SIGNAL(clicked(bool)),this,SLOT(onSettingBtnClicked()));
    connect(delete_btn,SIGNAL(clicked(bool)),this,SLOT(onDeleteBtnClicked()));
    connect(close_btn,SIGNAL(clicked(bool)),this,SLOT(onCloseBtnClicked()));
}

void TitleBar::setBtnsVisible(bool isVisible){
    new_btn->setVisible(isVisible);
    setting_btn->setVisible(isVisible);
    delete_btn->setVisible(isVisible);
    close_btn->setVisible(isVisible);
}

void TitleBar::mouseMoveEvent(QMouseEvent *event){
    if(m_bPressed){
        this->parentWidget()->parentWidget()->move(this->parentWidget()->parentWidget()->pos()
                                                   +event->pos()-m_point);
    }
    return QWidget::mouseMoveEvent(event);
}

void TitleBar::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        m_bPressed=true;
        m_point=event->pos();
    }
    return QWidget::mousePressEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event){
    m_bPressed=false;
    return QWidget::mouseReleaseEvent(event);
}

void TitleBar::onNewBtnClicked(){
    emit newBtnClickedSignal();
}

void TitleBar::onSettingBtnClicked(){
    emit settingBtnClickedSignal();
}

void TitleBar::onDeleteBtnClicked(){
    emit deleteBtnClickedSignal();
}

void TitleBar::onCloseBtnClicked(){
    emit closeBtnClickedSignal();
}


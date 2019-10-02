#include "styleoptionbar.h"

StyleOptionBar::StyleOptionBar(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(28);
    purpleStyle_btn=new QPushButton(this);
    yellowStyle_btn=new QPushButton(this);
    blueStyle_btn=new QPushButton(this);
    greenStyle_btn=new QPushButton(this);
    pinkStyle_btn=new QPushButton(this);
    whiteStyle_btn=new QPushButton(this);

    purpleStyle_btn->setObjectName("background: rgb(225,215,237);");
    yellowStyle_btn->setObjectName("background: rgb(255,242,181);");
    blueStyle_btn->setObjectName("background: rgb(202,232,255);");
    greenStyle_btn->setObjectName("background: rgb(199,239,196);");
    pinkStyle_btn->setObjectName("background: rgb(255,199,245);");
    whiteStyle_btn->setObjectName("background: rgb(243,243,243);");

    purpleStyle_btn->setStyleSheet("QPushButton{background: rgb(225,215,237);width:30px;height:20px;border:none;}"
                                   "QPushButton:hover:pressed:{none}");
    yellowStyle_btn->setStyleSheet("QPushButton{background: rgb(255,242,181);width:30px;height:20px;border:none;}"
                                   "QPushButton:hover:pressed:{none}");
    blueStyle_btn->setStyleSheet("QPushButton{background: rgb(202,232,255);width:30px;height:20px;border:none;}"
                                 "QPushButton:hover:pressed:{none}");
    greenStyle_btn->setStyleSheet("QPushButton{background: rgb(199,239,196);width:30px;height:20px;border:none;}"
                                  "QPushButton:hover:pressed:{none}");
    pinkStyle_btn->setStyleSheet("QPushButton{background: rgb(255,199,245);width:30px;height:20px;border:none;}"
                                 "QPushButton:hover:pressed:{none}");
    whiteStyle_btn->setStyleSheet("QPushButton{background: rgb(243,243,243);width:30px;height:20px;border:none;}"
                                  "QPushButton:hover:pressed:{none}");

    connect(purpleStyle_btn,SIGNAL(clicked(bool)),this,SLOT(onStyleBtnClicked()));
    connect(yellowStyle_btn,SIGNAL(clicked(bool)),this,SLOT(onStyleBtnClicked()));
    connect(blueStyle_btn,SIGNAL(clicked(bool)),this,SLOT(onStyleBtnClicked()));
    connect(greenStyle_btn,SIGNAL(clicked(bool)),this,SLOT(onStyleBtnClicked()));
    connect(pinkStyle_btn,SIGNAL(clicked(bool)),this,SLOT(onStyleBtnClicked()));
    connect(whiteStyle_btn,SIGNAL(clicked(bool)),this,SLOT(onStyleBtnClicked()));

    styleOptions=new QHBoxLayout(this);
    styleOptions->setContentsMargins(0,6,0,0);
    styleOptions->addStretch();
    styleOptions->addWidget(purpleStyle_btn);
    styleOptions->addWidget(yellowStyle_btn);
    styleOptions->addWidget(blueStyle_btn);
    styleOptions->addWidget(greenStyle_btn);
    styleOptions->addWidget(pinkStyle_btn);
    styleOptions->addWidget(whiteStyle_btn);
    styleOptions->addStretch();
}

StyleOptionBar::~StyleOptionBar(){
    delete purpleStyle_btn;
    delete yellowStyle_btn;
    delete blueStyle_btn;
    delete greenStyle_btn;
    delete pinkStyle_btn;
    delete whiteStyle_btn;
    delete styleOptions;
}

void StyleOptionBar::onStyleBtnClicked(){
    emit styleBtnClickedSignal(QObject::sender()->objectName());
}

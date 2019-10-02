#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notes.h"

#include <QFileIconProvider>
#include <QPainter>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QtDebug>
#include <QInputDialog>
#include <QLineEdit>
#include <QXmlStreamReader>
#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 90; // 设置每个tabBar中item的大小
            s.rheight() = 44;
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;

                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0x89cfff);
                    painter->setBrush(QBrush(0x89cfff));
                    painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);
                }
                else {
                    painter->setPen(0x5d5d5d);
                }

                painter->drawText(allRect, tab->text, option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabPosition(QTabWidget::West);
        ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);

    #if 0
        ui->tabWidget->setStyleSheet("QTabWidget::pane{ \
                border-left: 1px solid #eeeeee;\
            }");
    #endif

    readItemData();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addfile_triggered()
{

    QString file_full, file_name, file_path, file_suffix;
    //快捷方式原路径file_full
    //QStringList items_full=QFileDialog::getOpenFileNames(this);
    file_full = QFileDialog::getOpenFileName(this);


    if (!file_full.isEmpty())
    {
        QFileInfo fi = QFileInfo(file_full);
        //file_name = fi.fileName();
        file_name = fi.baseName();
        file_path = fi.absolutePath();
        file_suffix = fi.suffix();


//        int right=file_name.lastIndexOf('.');
//        QString filename = file_name.mid(0, right);


        QFileIconProvider icon_provider;
        QIcon icon = icon_provider.icon(fi);


        QListWidgetItem *item = new QListWidgetItem(icon, file_name, ui->listWidget);

        //ui->listWidget->addItem(item);

        QList<QListWidget*> listwidgetlist = ui->tabWidget->currentWidget()->findChildren<QListWidget*>();
        for(int i = 0; i < listwidgetlist.size(); i++)
        {
                QListWidget* itemlistw = listwidgetlist.at(i);
                itemlistw->addItem(item);
        }

        QPixmap pixmap = icon.pixmap(32,32);

        QString savepath ="./ItemIcons/";
        savepath += file_name+".png";
        pixmap.save(savepath, "png");   // savepath="./ItemIcons/iqiyi.png"



        QFile file("./ItemData.json");
        if(!file.open(QIODevice::ReadWrite)) {
            qDebug() << "File open failed!";
        } else {
            qDebug() <<"File open successfully!";
        }





        QJsonDocument jdc(QJsonDocument::fromJson(file.readAll()));

        qDebug()<<jdc.isArray();
        qDebug()<<jdc.isObject();
        qDebug()<<jdc.isEmpty();


        if(!jdc.isEmpty())
        {
            array = jdc.array();
        }

        QJsonObject obj1;
        obj1.insert("Name",file_name);
        obj1.insert("Path",file_full);
        obj1.insert("Count",0);
        array.push_back(obj1);

        //rootObj[ui->tabWidget->tabText(ui->tabWidget->currentIndex())]=array;

        QJsonDocument jdoc(array);

        file.seek(0);
        file.write(jdoc.toJson());
        file.flush();

    }
    else
    {
        return ;
    }







}


void MainWindow::on_addweb_triggered()
{

}

void MainWindow::on_setting_triggered()
{
    QFileInfo file_info("D:\\360Downloads\\Software\\IQIYI Video\\GeePlayer\\5.2.58.5088\\GeePlayer.exe");
    QFileIconProvider icon_provider;
    QIcon icon = icon_provider.icon(file_info);
    QPixmap pixmap = icon.pixmap(28,28);
    pixmap.save("D:\\test\\testqq.png", "png");

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();

}
void MainWindow::dropEvent(QDropEvent *event)
{

    QString fileurl = event->mimeData()->urls().first().toString();
    int left=fileurl.lastIndexOf('/');
    int right=fileurl.lastIndexOf('.');
    QString filename = fileurl.mid(left+1, right-left-1);
    ui->listWidget->addItem(filename);
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
//    QMenu* popMenu = new QMenu(this);
//    popMenu->addAction(new QAction(u8"添加", this));
//    popMenu->addAction(new QAction(u8"删除", this));
//    if(ui->listWidget->itemAt(mapFromGlobal(QCursor::pos())) != NULL) //如果有item则添加"修改"菜单 [1]*
//    {
//        popMenu->addAction(new QAction(u8"修改", this));
//    }

//    popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置

//    QPoint globalPos = ui->listWidget->mapToGlobal(pos);
//    // for QAbstractScrollArea and derived classes you would use:
//    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

//    QMenu myMenu;
//    myMenu.addAction("Menu Item 1");
//    // ...

//    QAction* selectedItem = myMenu.exec(globalPos);
//    if (selectedItem)
//    {
//        qDebug()<<"yes";
//    }
//    else
//    {
//        qDebug()<<"no";
//    }


    QListWidgetItem *selectedItem = ui->listWidget->itemAt(pos);
    QMenu menu;
    menu.addAction(ui->addfile);
    menu.addAction(ui->addweb);
    if (selectedItem)
    {
        menu.addAction(ui->delitem);
        menu.addAction(ui->modifyitem);
    }
    menu.exec(ui->listWidget->mapToGlobal(pos));
}



void MainWindow::on_tabWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu *popMenu =new QMenu(this);
    popMenu->addAction(ui->addfile);
    popMenu->addAction(ui->addweb);
    popMenu->addAction(ui->setting);

    popMenu->addAction(ui->addtabwidget);
    popMenu->addAction(ui->modifytabname);
    popMenu->addAction(ui->deltabwidget);
    popMenu->exec(QCursor::pos());
}

void MainWindow::on_addtabwidget_triggered()
{

    bool ok;
    QString tabname = QInputDialog::getText(this, u8"新建标签页",u8"请输入标签页名", QLineEdit::Normal,u8"NewTab",&ok);
    if (ok && !tabname.isEmpty())
    {
            QListWidget *wid=new QListWidget();
            ui->tabWidget->addTab(wid,tabname);
    }

}

void MainWindow::on_modifytabname_triggered()
{
    bool ok;
    QString tabname = QInputDialog::getText(this, u8"新建标签页",u8"请输入标签页名", QLineEdit::Normal,u8"TabName",&ok);
    if (ok && !tabname.isEmpty())
    {
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),tabname);
    }
}

void MainWindow::on_deltabwidget_triggered()
{
    QString tabname=ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    switch(QMessageBox::warning(this, u8"删除标签页", u8"此标签页下的所有项目将被删除，确定要删除"+tabname+u8"？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
    {
    case QMessageBox::Yes:
        ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
        break;
    case QMessageBox::No:
        break;

    }


}

void MainWindow::readItemData()
{

    QFile file("./ItemData.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() <<"File open successfully!";
    }


    QJsonParseError error;
    QJsonDocument doucment = QJsonDocument::fromJson(file.readAll(), &error);
    if (!doucment.isNull() && (error.error == QJsonParseError::NoError)) { //解析否出现错误
        if (doucment.isArray()) { // 数组判断
            QJsonArray array = doucment.array();  // 转数组
            for (int i = 0; i < array.count(); i++)
            {
                qDebug() <<"F!";
                QJsonValue value = array.at(i);


                QJsonObject subObj = value.toObject();

//                qDebug() << subObj.value("Count").toInt();
//                qDebug() << subObj.value("Path").toString();
//                qDebug() << subObj.value("Name").toString();

                QFileIconProvider icon_provider;
                QIcon icon = icon_provider.icon(subObj.value("Path").toString());


                QListWidgetItem *item = new QListWidgetItem(icon, subObj.value("Name").toString(), ui->listWidget);

                //ui->listWidget->addItem(item);

                QList<QListWidget*> listwidgetlist = ui->tabWidget->currentWidget()->findChildren<QListWidget*>();
                for(int i = 0; i < listwidgetlist.size(); i++)
                {
                        QListWidget* itemlistw = listwidgetlist.at(i);
                        itemlistw->addItem(item);
                }

            }
        }
    }



}



void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

    QFile file("./ItemData.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() <<"File open successfully!";
    }


    QJsonDocument jdc(QJsonDocument::fromJson(file.readAll()));
    QJsonArray ary=jdc.array();


    qDebug()<<item->text();
    for(int i=0; i<ary.size(); i++)
    {
        QJsonValue value = ary.at(i);
        QJsonObject obj=value.toObject();
        if(obj.value("Name").toString()==item->text())
        {
            qDebug()<<obj.value("Path").toString();
            QDesktopServices::openUrl(QUrl::fromLocalFile(obj.value("Path").toString()));
        }

    }














}

void MainWindow::on_delitem_triggered()
{

    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item) {
        delete item;
    }


    qDebug()<<ui->listWidget->currentItem()->text();

    qDebug()<<ui->listWidget->currentRow();


    QFile file("./ItemData.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() <<"File open successfully!";
    }
    QJsonDocument jdc(QJsonDocument::fromJson(file.readAll()));
    QJsonArray ary=jdc.array();
    ary.removeAt(ui->listWidget->currentRow());

    QJsonDocument jdoc(array);
    file.seek(0);
    file.write(jdoc.toJson());
    file.flush();



}

void MainWindow::on_modifyitem_triggered()
{
    qDebug()<<"modify";
}

void MainWindow::on_notes_triggered()
{
    QWidget *parent=new QWidget();

    int x=0;
    int y=0;
    int width=0;
    int height=0;
    int windowCount=0;
    QString style;
    QString content;
    Notes *newWindow=nullptr;

    QFile file("record.xml");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    if(file.exists()){
        QXmlStreamReader xmlReader(&file);
        xmlReader.readNext();
        while (!xmlReader.atEnd()) {
            if (xmlReader.isStartElement()) {
                if (xmlReader.name()=="window") {
                    windowCount++;
                }
                else if (xmlReader.name()=="x") {
                    x=xmlReader.readElementText().toInt();
                }
                else if (xmlReader.name()=="y") {
                    y=xmlReader.readElementText().toInt();
                }
                else if (xmlReader.name()=="width") {
                    width=xmlReader.readElementText().toInt();
                }
                else if (xmlReader.name()=="height") {
                    height=xmlReader.readElementText().toInt();
                }
                else if (xmlReader.name()=="style") {
                    style=xmlReader.readElementText();
                }
                else if (xmlReader.name()=="content") {
                    content=xmlReader.readElementText();
                    if (windowCount > 0){
                        newWindow=new Notes(parent);
                        newWindow->setGeometry(x,y,width,height);
                        newWindow->setStyle(style);
                        newWindow->setContentTest(content);
                        newWindow->show();
                    }
                }
            }
            xmlReader.readNextStartElement();
        }
    }
    file.close();
    if(windowCount==0){
        (new Notes(parent))->show();
    }
}

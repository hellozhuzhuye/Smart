#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonArray>
#include <QListWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_addfile_triggered();

    void on_addweb_triggered();

    void on_setting_triggered();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_tabWidget_customContextMenuRequested(const QPoint &pos);

    void on_addtabwidget_triggered();

    void on_modifytabname_triggered();

    void on_deltabwidget_triggered();



    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_delitem_triggered();

    void on_modifyitem_triggered();

    void on_notes_triggered();

private:
    Ui::MainWindow *ui;
    QJsonArray array;

protected:
    void dragEnterEvent(QDragEnterEvent *event); //拖动进入事件
    void dropEvent(QDropEvent *event);
    void readItemData();
};

#endif // MAINWINDOW_H

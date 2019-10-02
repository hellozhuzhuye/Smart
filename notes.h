#ifndef NOTES_H
#define NOTES_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QTextEdit>
#include <QString>
#include <QFocusEvent>

#include "titlebar.h"
#include "styleoptionbar.h"

class Notes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notes(QWidget *parent = nullptr);
    ~Notes();

    QString getContentText();
    void setContentTest(QString);
    void setStyle(QString& style);

private:
    TitleBar *titlebar;
    StyleOptionBar *styleOptionBar;
    QTextEdit *content;

    QStatusBar *statusBar;
    QVBoxLayout *content_layout;
    QWidget *parentW;
    QString style = "background: rgb(243,243,243);";

    void initTitlebar();


private slots:
    void onNewBtnClicked();
    void onSettingBtnClicked();
    void onDeleteBtnClicked();
    void onCloseBtnClicked();
    void onStyleBtnClicked(QString btnName);

protected:
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
};

#endif // NOTES_H

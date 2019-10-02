#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QPoint>
#include <QMouseEvent>
#include <QHBoxLayout>

#define BTN_WIDTH 24
#define TITLEBAR_HEIGHT 28

class TitleBar : public QWidget{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
    void setBtnsVisible(bool);

signals:
    void newBtnClickedSignal();
    void settingBtnClickedSignal();
    void deleteBtnClickedSignal();
    void closeBtnClickedSignal();

private slots:
    void onNewBtnClicked();
    void onSettingBtnClicked();
    void onDeleteBtnClicked();
    void onCloseBtnClicked();

private:
    QPushButton *new_btn;
    QPushButton *setting_btn;
    QPushButton *delete_btn;
    QPushButton *close_btn;
    QHBoxLayout *titlebar_layout;

    bool m_bPressed;
    QPoint m_point;

    void initControl();
    void initConnection();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // TITLEBAR_H

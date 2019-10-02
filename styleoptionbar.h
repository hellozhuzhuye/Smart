#ifndef STYLEOPTIONS_H
#define STYLEOPTIONS_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QString>

class StyleOptionBar : public QWidget
{
    Q_OBJECT
public:
    explicit StyleOptionBar(QWidget *parent = 0);
    ~StyleOptionBar();
signals:
    void styleBtnClickedSignal(QString);
private :
    QPushButton *purpleStyle_btn;
    QPushButton *yellowStyle_btn;
    QPushButton *blueStyle_btn;
    QPushButton *greenStyle_btn;
    QPushButton *pinkStyle_btn;
    QPushButton *whiteStyle_btn;
    QHBoxLayout *styleOptions;
private slots:
    void onStyleBtnClicked();
};

#endif // STYLEOPTIONS_H

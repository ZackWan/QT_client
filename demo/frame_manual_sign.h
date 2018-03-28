#ifndef FRAME_MANUAL_SIGN_H
#define FRAME_MANUAL_SIGN_H

#include <QWidget>

namespace Ui {
class Frame_manual_sign;
}

class Frame_manual_sign : public QWidget
{
    Q_OBJECT

public:
    explicit Frame_manual_sign(QWidget *parent = 0);
    ~Frame_manual_sign();

private slots:
    void on_btn_submit_clicked();//按钮绑定的槽函数
    void on_tb_id_textChanged(QString);//输入框改变文本的槽函数

private:
    Ui::Frame_manual_sign *ui;
    QString check_stu_existed_for_sign(QString);
};

#endif // FRAME_MANUAL_SIGN_H

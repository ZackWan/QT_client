#ifndef FRAME_STUMANAGE_H
#define FRAME_STUMANAGE_H

#include <QWidget>

namespace Ui {
class Frame_stuManage;
}

class Frame_stuManage : public QWidget
{
    Q_OBJECT

public:
    explicit Frame_stuManage(QWidget *parent = 0);
    ~Frame_stuManage();
private slots:
    void on_btn_addFace_clicked();//按钮绑定的槽函数
    void on_btn_updateFace_clicked();
    void on_btn_delete_clicked();
    void on_tb_id_update_textChanged(QString);//两个输入框文本改变的函数
    void on_tb_id_delete_textChanged(QString);



private:
    Ui::Frame_stuManage *ui;
};

#endif // FRAME_STUMANAGE_H

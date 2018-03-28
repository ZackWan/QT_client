#include "frame_manual_sign.h"
#include "ui_frame_manual_sign.h"
#include <QMessageBox>

Frame_manual_sign::Frame_manual_sign(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frame_manual_sign)
{
    ui->setupUi(this);
    ui->btn_submit->setEnabled(false);
    ui->tb_id->setPlaceholderText(QString::fromUtf8("请输入学号"));
    ui->stu_name->setVisible(false);
}

Frame_manual_sign::~Frame_manual_sign()
{
    delete ui;
}

QString Frame_manual_sign::check_stu_existed_for_sign(QString id)
{
    //判断输入是否合法以及学号是否已存在，用于更新和删除学生,返回学生姓名或一个特殊串表示失败

    //测试用
    if(id==NULL)
        return QString("NULL");//危险的写法
    else{

        return QString("小泽");
    }
}

void Frame_manual_sign::on_btn_submit_clicked()
{
    QString id=ui->tb_id->text();
    QString name=ui->tip_name->text();

         QMessageBox msgBox;
      msgBox.setText(id+name);
      msgBox.setInformativeText("turn up");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Ok);
      int ret = msgBox.exec();
      switch (ret) {
          case QMessageBox::Ok:
              // Ok was clicked
              break;
          case QMessageBox::Cancel:
              // Cancel was clicked
              break;
          default:
              // should never be reached
              break;
        }


}

void Frame_manual_sign::on_tb_id_textChanged(QString id)
{
    QString flag=check_stu_existed_for_sign(id);

    if(flag=="NULL"){//为空或者不合法不存在
        ui->btn_submit->setEnabled(false);
        ui->stu_name->setVisible(false);
        ui->tip_name->clear();
    }
    else{
        ui->btn_submit->setEnabled(true);
        ui->stu_name->setVisible(true);
        ui->tip_name->setText(flag);
    }
}

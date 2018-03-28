#include "frame_stumanage.h"
#include "ui_frame_stumanage.h"
#include "frame_sign.h"
#include <QMessageBox>

#define FirstTime 1

Frame_stuManage::Frame_stuManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frame_stuManage)
{
     ui->setupUi(this);
     ui->btn_updateFace->setEnabled(false);
     ui->btn_delete->setEnabled(false);
     ui->addstu_id_LineEdit->setPlaceholderText(QString::fromUtf8("请输入学号"));
     ui->addstu_name_LineEdit->setPlaceholderText(QString::fromUtf8("请输入姓名"));
     ui->tb_id_update->setPlaceholderText(QString::fromUtf8("请输入学号"));
     ui->tb_id_delete->setPlaceholderText(QString::fromUtf8("请输入学号"));

     ui->upstu_name_Label->setVisible(false);
     ui->destu_name_Label->setVisible(false);
}

Frame_stuManage::~Frame_stuManage()
{
    delete ui;
}

int check_add_input(QString id,QString name)
{
    //判断输入是否合法以及学号是否已存在，用于添加学生

    //测试用
    if(id==NULL||name==NULL)
        return -1;
    return 1;
}

void Frame_stuManage::on_btn_addFace_clicked()
{
    QString id=ui->addstu_id_LineEdit->text();
    QString name=ui->addstu_name_LineEdit->text();
    int flag=check_add_input(id,name);
    if(flag==-1){
        QMessageBox::warning(this,tr("警告"),tr("输入不合法!/或者学号已存在"),QMessageBox::Yes);
        this->ui->addstu_id_LineEdit->clear();
        this->ui->addstu_name_LineEdit->clear();
        this->ui->addstu_id_LineEdit->setFocus();
    }
    else{
        Frame_sign *fs=new Frame_sign(FirstTime);
        fs->setParent(ui->stu_add);
        fs->show();

        ui->addstu_id_LineEdit->clear();
        ui->addstu_name_LineEdit->clear();
    }
}

void Frame_stuManage::on_btn_updateFace_clicked()
{
    Frame_sign *fs=new Frame_sign(FirstTime);
    fs->setParent(ui->stu_update);
    fs->show();

    ui->tb_id_update->clear();
    ui->tip_name_update->clear();
}

void Frame_stuManage::on_btn_delete_clicked()
{
    QString id=ui->tb_id_delete->text();
    QString name=ui->tip_name_delete->text();

    QMessageBox msgBox;
      msgBox.setText(id+" "+name+" 的信息将会被删除");
      msgBox.setInformativeText("确定删除吗？");
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


QString check_stu_existed(QString id)
{
    //判断输入是否合法以及学号是否已存在，用于更新和删除学生,返回学生姓名或一个特殊串表示失败

    //测试用
    if(id==NULL)
        return QString("NULL");//危险的写法
    return QString("小泽");
}

//更新学生 学号输入框 文本改变时的函数 合法且有效时按钮才enable
void Frame_stuManage::on_tb_id_update_textChanged(QString id)
{
    QString flag=check_stu_existed(id);

    if(flag=="NULL"){//为空或者不合法不存在
        ui->btn_updateFace->setEnabled(false);
        ui->upstu_name_Label->setVisible(false);
        ui->tip_name_update->clear();
    }
    else{
        ui->btn_updateFace->setEnabled(true);
        ui->upstu_name_Label->setVisible(true);
        ui->tip_name_update->setText(flag);
    }

}

//删除学生 学号输入框 文本改变时的函数 合法且有效时按钮才enable
void Frame_stuManage::on_tb_id_delete_textChanged(QString id)
{
    QString flag=check_stu_existed(id);

    if(flag=="NULL"){//为空或者不合法不存在
        ui->btn_delete->setEnabled(false);
        ui->destu_name_Label->setVisible(false);
        ui->tip_name_delete->clear();
    }
    else{
        ui->btn_delete->setEnabled(true);
        ui->destu_name_Label->setVisible(true);
        ui->tip_name_delete->setText(flag);
    }
}

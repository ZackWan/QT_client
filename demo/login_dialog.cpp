#include "login_dialog.h"
#include "ui_login_dialog.h"
#include "httpop.h"

#include <QByteArray>
#include <QCryptographicHash>

Login_Dialog::Login_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Dialog)
{
    ui->setupUi(this);
}

Login_Dialog::~Login_Dialog()
{
    delete ui;
}

//检查老师ID和密码
int check_teacher_id(QString id,QString password)
{
    //此处应为查询后台
    //密码使用md5加密
    QByteArray btarray;
    btarray.append(password);
    QByteArray hash_btarray=QCryptographicHash::hash(btarray,QCryptographicHash::Md5);
    QString md5_p=hash_btarray.toHex();

    //HttpOp* ho = new HttpOp();
    //QString strUrl ;//咋写

   //connect(ho,SIGNAL(signal_requestFinished(bool,const QString&)), //http请求结束信号
            //this,SLOT(slot_requestFinished(bool,const QString&)));

    //ho->sendRequest(strUrl,"post");

    //测试用
    if(id==NULL||password==NULL)
        return -1;
    return 1;
}

//点击登录
void Login_Dialog::on_btn_login_clicked()
{
    QString id=ui->tb_id->text();
    QString password=ui->tb_password->text();

    int flag=check_teacher_id(id,password);
    if(flag==1){//检查
        this->teacher_id=id;
        accept();
    }
    else if(flag==-1){
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
        this->ui->tb_id->clear();
        this->ui->tb_password->clear();
        this->ui->tb_id->setFocus();
    }
}


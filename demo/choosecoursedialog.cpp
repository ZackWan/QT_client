#include "choosecoursedialog.h"
#include "ui_choosecoursedialog.h"
#include "httpop.h"

#include <QStandardItemModel>
#include <QDebug>


ChooseCourseDialog::ChooseCourseDialog(QString id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCourseDialog)
{
    ui->setupUi(this);
    ui->lb_id_pro->setText(id);

    this->get_teacher_info(id);
    this->get_courselist(id);//上面两个操作可能会有时间上的延后,所以把显示操作放在Json数据处理完后执行

    ui->noChoiceWarning->setVisible(false);
}

ChooseCourseDialog::~ChooseCourseDialog()
{
    delete ui;//这里删掉后还要返回登录窗口或者关闭主窗口
}

void ChooseCourseDialog::get_courselist(QString id)
{
    //根据老师id获取课程列表
    HttpOp* ho = new HttpOp();
    //设置URL
    QString strUrl = ho->reBaseUrl();
    strUrl += ("/teacherCourse/" +id);

    connect(ho,SIGNAL(signal_requestFinished(bool,QNetworkReply&)), //http请求结束信号
            this,SLOT(slot_requestCourseFinished(bool,QNetworkReply&)));

    qDebug() << strUrl << endl;
    ho->sendRequest(strUrl,"get");
}

void ChooseCourseDialog::get_teacher_info(QString id)
{
    HttpOp* ho = new HttpOp();
    //设置URL
    QString strUrl = ho->reBaseUrl();
    strUrl += ("/teacher/" +id);

    connect(ho,SIGNAL(signal_requestFinished(bool,QNetworkReply&)),
            this,SLOT(slot_requestTeacherFinished(bool,QNetworkReply&)));//http请求结束信号

    qDebug() << strUrl << endl;
    ho->sendRequest(strUrl,"get");

    qDebug()<<teacher_name;//奇怪的问题，到了这里slot_requestTeacherFinished还没有执行
}

void ChooseCourseDialog::slot_requestTeacherFinished(bool bSuccess, QNetworkReply &reply)
{
    if(bSuccess)
    {
        qDebug() <<"request finished"<< reply.Text;
        QJsonParseError p_error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(reply.readAll(),&p_error);

        if(p_error.error == QJsonParseError::NoError){
            if(!(jsonDocument.isNull()||jsonDocument.isEmpty())){
                if(jsonDocument.isObject())
                {
                    QJsonObject object = jsonDocument.object();
                    QJsonValue value = object.value("name");//取出key为name的值
                    //判断是否是string类型
                    qDebug()<<"value:"<<value.isString();
                    if (value.isString())
                        teacher_name = value.toString();
                    qDebug()<<teacher_name;
                    ui->lb_name_pro->setText(teacher_name);
                }
            }
        }
    }
    else
    {
        qDebug()<<"请求失败！";
    }
}

void ChooseCourseDialog::slot_requestCourseFinished(bool bSuccess, QNetworkReply &reply)
{
    if(bSuccess)
    {
        course_model = new QStandardItemModel();
        //qDebug() <<"request finished"<< reply.Text;
        QJsonParseError p_error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(reply.readAll(),&p_error);

        if(p_error.error == QJsonParseError::NoError){
            if(!(jsonDocument.isNull()||jsonDocument.isEmpty())){
                if(jsonDocument.isObject())
                {
                    QJsonObject object = jsonDocument.object();
                    if(object.contains("teacher_course")){
                        QJsonValue valueArray = object.value("teacher_course");
                        if (valueArray.isArray())//判断类型是否为array，并且将array遍历出来
                        {
                            QJsonArray array = valueArray.toArray();
                            QStandardItem *item;
                            for(int i=0;i<array.size();i++)
                            {
                                QJsonValue value = array[i];

                                //似乎Json里面的数字只能用toInt函数，再转成String
                                //item = new QStandardItem(QString("%1").arg(value["courseId"].toInt()));
                                item = new QStandardItem(QString::number(value["id"].toInt(),10));
                                //course_model->item(i,0)->setTextAlignment(Qt::AlignCenter);
                                course_model->setItem(i,0,item);

                                item = new QStandardItem(value["courseName"].toString());
                                //course_model->item(i,1)->setTextAlignment(Qt::AlignCenter);
                                course_model->setItem(i,1,item);

                                item = new QStandardItem(value["courseInfo"].toString());
                                //course_model->item(i,1)->setTextAlignment(Qt::AlignCenter);
                                course_model->setItem(i,2,item);
                            }
                        }
                    }
                }
            }
        }

        show_courselist();
    }
    else
    {
        qDebug()<<"请求失败！";
    }
}

void ChooseCourseDialog::on_btn_test_clicked()
{
    int row_selected = ui->tableView->currentIndex().row();//获取选中的行

    if(row_selected == -1)//未选择任何选项
    {
        ui->noChoiceWarning->setVisible(true);
        return;//不放行
    }
    else
    {
        //根据row进行网络请求...,似乎又不需要
    }

    course_id = course_model->item(row_selected,0)->text().toInt();//course=course_id[row_selected]

    accept();
}

void ChooseCourseDialog::show_courselist()
{
    QStringList labels = QObject::trUtf8("课程ID,课程名称,上课时间").simplified().split(",");
    course_model->setHorizontalHeaderLabels(labels);

    ui->tableView->setModel(course_model);
    ui->tableView->setShowGrid(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//内容不可编辑
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::
                                                            ResizeToContents);//设置列宽随文本增长
    ui->tableView->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);//设置鼠标不可改变列宽
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能选择一行，不能多行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//单击选择一行
    ui->tableView->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白
    QHeaderView *header = ui->tableView->horizontalHeader();
    header->setStretchLastSection(true);
    ui->tableView->show();
}














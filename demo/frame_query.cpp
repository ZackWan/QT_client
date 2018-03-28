#include "frame_query.h"
#include "ui_frame_query.h"

Frame_query::Frame_query(int course_id, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Frame_query)
{
    ui->setupUi(this);
    ui->signedNum->setVisible(false);
    ui->unSignedNum->setVisible(false);

    this->get_signList(course_id);

    connect(ui->courseSign,SIGNAL(doubleClicked(const QModelIndex &)),
            this,SLOT(get_signInfo(const QModelIndex &)));//双击选择
}

Frame_query::~Frame_query()
{
    delete ui;
}

void Frame_query::get_signList(int course_id) //根据课程id获取签到列表
{
    HttpOp* ho = new HttpOp();
    //设置URL
    QString strUrl = ho->reBaseUrl();
    strUrl += ("/courseSign/" +QString::number(course_id,10));

    connect(ho,SIGNAL(signal_requestFinished(bool,QNetworkReply&)), //http请求结束信号
            this,SLOT(slot_requestCourseSignFinished(bool,QNetworkReply&)));

    qDebug() << strUrl << endl;
    ho->sendRequest(strUrl,"get");
}

void Frame_query::get_signInfo(const QModelIndex & id)
{
    HttpOp* ho = new HttpOp();
    //设置URL
    QString strUrl = ho->reBaseUrl();
    strUrl += ("/signSignDetail/" +QString::number(id.row()+1,10));

    connect(ho,SIGNAL(signal_requestFinished(bool,QNetworkReply&)), //http请求结束信号
            this,SLOT(slot_requestSignInfoFinished(bool,QNetworkReply&)));

    qDebug() << strUrl << endl;
    ho->sendRequest(strUrl,"get");
}

void Frame_query::queryAll_byStudent()
{

}

void Frame_query::slot_requestCourseSignFinished(bool bSuccess, QNetworkReply &reply)
{
    if(bSuccess)
    {
        courseSign_model = new QStandardItemModel();
        QJsonParseError p_error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(reply.readAll(),&p_error);

        if(p_error.error == QJsonParseError::NoError){
            if(!(jsonDocument.isNull()||jsonDocument.isEmpty())&&jsonDocument.isObject()){
                QJsonObject object = jsonDocument.object();
                if(object.contains("course_sign")){
                    QJsonValue valueArray = object.value("course_sign");
                    if (valueArray.isArray())//判断类型是否为array，并且将array遍历出来
                    {
                        QJsonArray array = valueArray.toArray();
                        QStandardItem *item;

                        for(int i=0;i<array.size();i++)
                        {
                            QJsonValue value = array[i];
                            //似乎Json里面的数字只能用toInt函数，再转成String
                            item = new QStandardItem(QString::number(value["id"].toInt(),10));
                            courseSign_model->setItem(i,0,item);
                            courseSign_model->item(i,0)->setTextAlignment(Qt::AlignCenter);

                            item = new QStandardItem(value["signTime"].toString());
                            courseSign_model->setItem(i,1,item);
                            courseSign_model->item(i,1)->setTextAlignment(Qt::AlignCenter);
                        }
                        this->show_courseSignlist();
                    }
                }
            }
        }
    }
    else
    {
        qDebug()<<"请求失败！";
    }
}

void Frame_query::slot_requestSignInfoFinished(bool bSuccess, QNetworkReply &reply)
{
    if(bSuccess)
    {
        signInfo_model = new QStandardItemModel();
        QJsonParseError p_error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(reply.readAll(),&p_error);

        int r=0;
        if(p_error.error == QJsonParseError::NoError){
            if(!(jsonDocument.isNull()||jsonDocument.isEmpty())&&jsonDocument.isObject()){
                QJsonObject object = jsonDocument.object();
                if(object.contains("signNum")){
                    QJsonValue value = object.value("signNum");
                    QString t = tr("签到人数: ");
                    ui->signedNum->setText(t+QString::number(value.toInt(),10));
                }
                if(object.contains("nonsignNum")){
                    QJsonValue value = object.value("nonsignNum");
                    QString t = tr("未签到人数: ");
                    ui->unSignedNum->setText(t+QString::number(value.toInt(),10));
                }
                if(object.contains("signList")){
                    QJsonValue valueArray = object.value("signList");
                    if (valueArray.isArray())//判断类型是否为array，并且将array遍历出来
                    {
                        QJsonArray array = valueArray.toArray();
                        r = arrayProcess(array,true,r);
                    }
                }
                if(object.contains("nonsignList")){
                    QJsonValue valueArray = object.value("nonsignList");
                    qDebug()<<valueArray.isArray();
                    if (valueArray.isArray())//判断类型是否为array，并且将array遍历出来
                    {
                        QJsonArray array = valueArray.toArray();
                        arrayProcess(array,false,r);
                    }
                }
                this->show_signInfolist();
                ui->signedNum->setVisible(true);
                ui->unSignedNum->setVisible(true);
            }
        }
    }
    else
    {
        qDebug()<<"请求失败！";
    }
}

int Frame_query::arrayProcess(QJsonArray array, bool is_signed, int r)
{
    QStandardItem *item;
    int i=0;
    for(i=r;i<array.size()+r;i++)
    {
        QJsonValue value = array[i-r];//需注意

        item = new QStandardItem(value["stuId"].toString());
        signInfo_model->setItem(i,0,item);
        signInfo_model->item(i,0)->setTextAlignment(Qt::AlignCenter);

        item = new QStandardItem(value["name"].toString());
        signInfo_model->setItem(i,1,item);
        signInfo_model->item(i,1)->setTextAlignment(Qt::AlignCenter);

        item = new QStandardItem(value["signKind"].toString());
        signInfo_model->setItem(i,2,item);
        signInfo_model->item(i,2)->setTextAlignment(Qt::AlignCenter);
        qDebug()<<value["signKind"].toString();

        if(is_signed)
            item = new QStandardItem(value["signTime"].toString());
        else
            item = new QStandardItem(" ");
        signInfo_model->setItem(i,3,item);
        signInfo_model->item(i,3)->setTextAlignment(Qt::AlignCenter);
    }
    return i;
}

void Frame_query::show_courseSignlist()
{
    QStringList labels = QObject::trUtf8("签到ID,签到时间").simplified().split(",");
    courseSign_model->setHorizontalHeaderLabels(labels);

    ui->courseSign->setModel(courseSign_model);
    ui->courseSign->setShowGrid(false);
    ui->courseSign->setEditTriggers(QAbstractItemView::NoEditTriggers);//内容不可编辑
    ui->courseSign->horizontalHeader()->setSectionResizeMode(QHeaderView::
                                                            ResizeToContents);//设置列宽随文本增长
    ui->courseSign->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);//设置鼠标不可改变列宽
    ui->courseSign->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能选择一行，不能多行选中
    ui->courseSign->setSelectionBehavior(QAbstractItemView::SelectRows);//单击选择一行
    ui->courseSign->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白
    QHeaderView *header = ui->courseSign->horizontalHeader();
    header->setStretchLastSection(true);
    ui->courseSign->show();
}

void Frame_query::show_signInfolist()
{
    QStringList labels = QObject::trUtf8("学号,姓名,签到方式,签到时间").simplified().split(",");
    signInfo_model->setHorizontalHeaderLabels(labels);

    ui->signInfo->setModel(signInfo_model);
    ui->signInfo->setShowGrid(false);
    ui->signInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);//内容不可编辑
    ui->signInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::
                                                            ResizeToContents);//设置列宽随文本增长
    ui->signInfo->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);//设置鼠标不可改变列宽
    ui->signInfo->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能选择一行，不能多行选中
    ui->signInfo->setSelectionBehavior(QAbstractItemView::SelectRows);//单击选择一行
    ui->signInfo->setAlternatingRowColors(true);//设置隔一行变一颜色，即：一灰一白
    QHeaderView *header = ui->signInfo->horizontalHeader();
    header->setStretchLastSection(true);
    ui->signInfo->show();
}

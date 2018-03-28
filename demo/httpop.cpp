#include <httpop.h>

#include <QTextCodec>

const int nHTTP_TIME = 10000; //10秒

HttpOp::HttpOp(QObject *parent) :
    QObject(parent)
{
    m_pNetworkManager = new QNetworkAccessManager(this);
    m_pNetworkReply = NULL;
    m_pTimer = new QTimer;
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(slot_requestTimeout()));//超时信号
}

QString HttpOp::reBaseUrl()
{
    return BaseUrl;
}

void HttpOp::sendRequest(const QString &strUrl, QString op)
{
    m_strUrl = strUrl;
    QNetworkRequest netRequest;
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    netRequest.setUrl(QUrl(strUrl)); //地址信息

    if(op == "get")
    {
        m_pNetworkReply = m_pNetworkManager->get(netRequest); //发起get请求
    }
    else if(op == "post")
    {
        QString strBody; //http body部分，可封装参数信息
        //不知道写点啥

        QByteArray contentByteArray = strBody.toLatin1();//转成二进制
        m_pNetworkReply = m_pNetworkManager->post(netRequest,contentByteArray);
    }

    connect(m_pNetworkReply,SIGNAL(finished()),this,SLOT(slot_requestFinished())); //请求完成信号
    m_pTimer->start(nHTTP_TIME);
}

//请求结束
void HttpOp::slot_requestFinished()
{
    m_pTimer->stop();//关闭定时器
    int nHttpCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
    if(nHttpCode == 200)//成功
    {
        qDebug()<<nHttpCode;
        emit signal_requestFinished(true,*m_pNetworkReply);//请求成功
    }
    else
    {
        qDebug()<<nHttpCode;
        emit signal_requestFinished(false,*m_pNetworkReply);//请求失败
    }
    m_pNetworkReply->deleteLater();
    this->deleteLater(); //释放内存
}

//请求超时
void HttpOp::slot_requestTimeout()
{
    emit signal_requestFinished(false,*m_pNetworkReply);//请求失败
    m_pNetworkReply->deleteLater();
    this->deleteLater();//释放内存
}

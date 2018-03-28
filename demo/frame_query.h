#ifndef FRAME_QUERY_H
#define FRAME_QUERY_H

#include <QWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QObject>
#include <QString>


#include <httpop.h>

namespace Ui {
class Frame_query;
}

class Frame_query : public QWidget
{
    Q_OBJECT

public:
    //explicit Frame_query(QWidget *parent = 0);
    explicit Frame_query(int course_id,QWidget *parent = 0);
    ~Frame_query();
    QString order;//每一周内的上课时间，如“周二 3 4节（双）”，类型待定
    QString stuid;//学生学号

    void show_courseSignlist();
    void show_signInfolist();
    int arrayProcess(QJsonArray ,bool,int);

    void get_sign_info(QString id);
    void slot_requestSignFinished(bool bSuccess, QNetworkReply &reply);//结果处理

private slots:
    void get_signList(int course_id);//查询本学期每次课出勤状况
    void get_signInfo(const QModelIndex &);
    void queryAll_byStudent();//查询本学期所有学生出勤情况
    void slot_requestCourseSignFinished(bool bSuccess, QNetworkReply &reply);
    void slot_requestSignInfoFinished(bool bSuccess, QNetworkReply &reply);


private:
    Ui::Frame_query *ui;
    QStandardItemModel* courseSign_model;//表格显示内容
    QStandardItemModel* signInfo_model;//表格显示内容
};

#endif // FRAME_QUERY_H

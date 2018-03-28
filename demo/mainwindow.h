#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTabBar>
#include <QPushButton>

#include "mytitlebar.h"
#include "tabwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString id,QWidget *parent = 0);
    ~MainWindow();

    QString teacher_id;//当前老师工号
    int course_id;//选中的课程id
    TabWidget * tabWidget ;
    //添加数据成员，当前课程
    QPushButton * change_course;
    QPushButton * change_login;

    TitleBar* m_titleBar;


private slots:
   void on_change_course_clicked();//按钮绑定的槽函数
   void on_change_login_clicked();
   void on_tabwidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    void initTitleBar();
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "frame_sign.h"
#include "frame_query.h"
#include "frame_stumanage.h"
#include "frame_manual_sign.h"
#include "choosecoursedialog.h"
#include "login_dialog.h"

#include <QLayout>
#include <QtUiTools\QUiLoader>
#include <QPushButton>

MainWindow::MainWindow(QString teacherId,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // FramelessWindowHint属性设置窗口去除边框;
    // WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);// 设置窗口背景透明;

    initTitleBar();

    this->teacher_id=teacherId;//获得输入老师id

    this->tabWidget = new TabWidget(Qt::Horizontal);
    tabWidget->setTabPosition(QTabWidget::West);
    tabWidget->move(0,30);

    //选择课程
    tabWidget->hide();
    tabWidget->tabBar()->setStyleSheet(QString("font:17pt"));
    tabWidget->setParent(this);
  //  ui->mainLayout->addWidget(tabWidget);
    QObject::connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(on_tabwidget_currentChanged(int)));

    ChooseCourseDialog *cc_dialog=new ChooseCourseDialog(teacherId);
    if(cc_dialog->exec()==QDialog::Accepted)
    {
        this->course_id=cc_dialog->course_id;
        tabWidget->show();
        qDebug()<<course_id;
    }

    Frame_sign * fs=new Frame_sign;
    fs->setStyleSheet("backgroud:white;");
    tabWidget->addTab(fs,QIcon(":/assets/img/face_sign.png"), QString(tr("学生签到")));

    Frame_query *fq=new Frame_query(course_id);
    tabWidget->addTab(fq,QIcon(":/assets/img/query.png"),QString(tr("信息查询")));

    Frame_stuManage *fm=new Frame_stuManage;
    tabWidget->addTab(fm,QIcon(":/assets/img/stumanage.png"),QString(tr("学生管理")));

    Frame_manual_sign *fms=new Frame_manual_sign;
    tabWidget->addTab(fms,QIcon(":/assets/img/manual_sign.png"),QString(tr("手动签到")));

    change_course=new QPushButton(this);
    change_course->setIcon(QIcon(":/assets/img/change_course.png"));
    change_course->setText("切换课程");
    change_course->setStyleSheet("QPushButton{border: none;border-radius:0px;background:#00a99d;}QPushButton::hover{background: #65dbdb;}");
    change_course->move(20,280);
    QObject::connect(change_course,SIGNAL(clicked()),this,SLOT(on_change_course_clicked()));

    change_login=new QPushButton(this);
    change_login->setIcon(QIcon(":/assets/img/change_login.png"));
    change_login->setText("退出登录");
    change_login->setStyleSheet("QPushButton{border: none;border-radius:0px;background:#00a99d;}QPushButton::hover{background: #65dbdb;}");
    change_login->move(20,310);
    QObject::connect(change_login,SIGNAL(clicked()),this,SLOT(on_change_login_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTitleBar()
{   m_titleBar = new TitleBar(this);
    installEventFilter(m_titleBar);

    setWindowTitle("人脸识别课堂签到系统");
    setWindowIcon(QIcon(":/assets/img/face_sign.png"));

    m_titleBar->setTitleContent("人脸识别课堂签到系统");
    m_titleBar->setTitleWidth(this->width());
}

void MainWindow::on_change_course_clicked()
{   
    this->hide();
    ChooseCourseDialog *cc_dialog=new ChooseCourseDialog(this->teacher_id);
    if(cc_dialog->exec()==QDialog::Accepted)
    {
        course_id=cc_dialog->course_id;
    }

    this->show();
}

void MainWindow::on_change_login_clicked()
{
    this->hide();
    Login_Dialog *dialog=new Login_Dialog();
    if(dialog->exec()==QDialog::Accepted)
    {
        teacher_id=dialog->teacher_id;
        ChooseCourseDialog *cc_dialog=new ChooseCourseDialog(this->teacher_id);
        if(cc_dialog->exec()==QDialog::Accepted)
        {
            course_id=cc_dialog->course_id;
        }

    }
    //this->tabWidget->show();
    this->show();
}

void MainWindow::on_tabwidget_currentChanged(int index)
{
        qDebug()<<"current index:"<<index;
        if(index!=0){
            ;
        }
}

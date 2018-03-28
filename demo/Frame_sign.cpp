#include "frame_sign.h"
#include "ui_Frame_sign.h"

Frame_sign::Frame_sign(int flag,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frame_sign)
{
    ui->setupUi(this);

    camera=new QCamera(this);
    viewfinder=new QCameraViewfinder(this);
    imageCapture=new QCameraImageCapture(camera);

    camera->setViewfinder(viewfinder);
    ui->ImageView->addWidget(viewfinder);
    ui->ImageCapture->setScaledContents(true);

    if(flag==1){//为录入信息时
        this->camera->start();
        ui->buttonQuit->setText(QString(tr("结束录入")));
        ui->view_start->hide();

        connect(ui->buttonCapture, SIGNAL(clicked()), this, SLOT(captureImage()));
        connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(saveImage()));
        connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(displayImage(int,QImage)));
        connect(ui->buttonQuit, SIGNAL(clicked()), this, SLOT(sign_first_over()));

    }
    else{ //为正常签到时
        ui->view_sign->hide();
        ui->view_first->hide();

        connect(ui->btn_start,SIGNAL(clicked()), this, SLOT(sign_start()));
        connect(ui->buttonQuit, SIGNAL(clicked()), this, SLOT(sign_over()));
    }




}

Frame_sign::~Frame_sign()
{
    delete ui;
}

void Frame_sign::sign_start()
{
    ui->view_start->hide();
    ui->view_sign->show();
    this->camera->start();
}

void Frame_sign::sign_first_over()
{
    //保存工作等

    this->camera->stop();
  //  ui->ImageCapture->clear();
    this->close();
}

void Frame_sign::sign_over()
{
    this->camera->stop();
    //viewfinder->hide();
    ui->view_sign->hide();
    ui->view_start->show();
}

void Frame_sign::captureImage()
{
//ui->statusBar->showMessage(tr("capturing..."), 1000);
imageCapture->capture();
}

void Frame_sign::displayImage(int , QImage image)
{
    ui->ImageCapture->setPixmap(QPixmap::fromImage(image));

//ui->statusBar->showMessage(tr("capture OK!"), 5000);
}

void Frame_sign::saveImage()
{
QString fileName=QFileDialog::getSaveFileName(this, tr("save file"), QDir::homePath(), tr("jpegfile(*.jpg)"));
if(fileName.isEmpty()) {
//ui->statusBar->showMessage(tr("save cancel"), 5000);
return;
}
const QPixmap* pixmap=ui->ImageCapture->pixmap();
if(pixmap) {
pixmap->save(fileName);
//ui->statusBar->showMessage(tr("save OK"), 5000);
}
}

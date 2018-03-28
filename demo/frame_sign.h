#ifndef Frame_sign_H
#define Frame_sign_H

#include <QWidget>
#include <QtMultimedia\QCamera>
#include <QtMultimediaWidgets\QCameraViewfinder>
#include <QtMultimedia\QCameraImageCapture>
#include <QFileDialog>

namespace Ui {
class Frame_sign;
}
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;

class Frame_sign : public QWidget
{
    Q_OBJECT
public:
    explicit Frame_sign(int flag=0,QWidget *parent = 0);
    ~Frame_sign();

private slots:
void captureImage();
void displayImage(int,QImage);
void saveImage();
void sign_over();
void sign_start();
void sign_first_over();

private:
    Ui::Frame_sign *ui;

    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
};

#endif // Frame_sign_H

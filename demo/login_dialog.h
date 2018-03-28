#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class Login_Dialog;
}

class Login_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Login_Dialog(QWidget *parent = 0);
    ~Login_Dialog();
    QString teacher_id;
private:
    Ui::Login_Dialog *ui;

private slots:
    void on_btn_login_clicked();
};

#endif // LOGIN_DIALOG_H

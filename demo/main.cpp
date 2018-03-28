#include "mainwindow.h"
#include "login_dialog.h"

#include <QFile>
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QFile f(":/assets/StyleSheet.css");
    if (f.open(QIODevice::ReadOnly)) {
        a.setStyleSheet(f.readAll());
        f.close();
    }

    Login_Dialog ld;
    if(ld.exec()==QDialog::Accepted)
       {
            MainWindow w(ld.teacher_id);
            w.show();
            return a.exec();
       }
       else return 0;
}

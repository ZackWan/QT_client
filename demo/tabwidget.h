#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QTabBar>
#include <tabstyle.h>

class TabWidget : public QTabWidget
{
public:
    QTabBar * tab_bar;
    explicit TabWidget(Qt::Orientation orientation, QWidget * parent = 0)
        : QTabWidget(parent)
    {
         tab_bar= new QTabBar;
        tab_bar->setStyle(new TabStyle(orientation));
        tab_bar->setStyleSheet("backgroud:rgb(0,169,157);");
        setTabBar(tab_bar);
    }
};

#endif // TABWIDGET_H

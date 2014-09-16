#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QSound>
#include "mapwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    MapWidget m_map;
    QSound *music;
};

#endif // MAINWIDGET_H

#include "mainwindow.h"
#include <QApplication>
#include <QSound>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSound *music = new QSound("res/bg_music.wav");
    music->setLoops(-1);
    music->play();

    return a.exec();
}

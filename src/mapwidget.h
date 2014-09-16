#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QtWidgets>

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    MapWidget(QWidget *parent = 0);
    ~MapWidget();
    QSize sizeHint() const;
    QSize minimumSize() const;
    QSize maximumSize() const;
    void changeCellState(int x, int y);

private:
    enum mode {
        RANDOM = 0,
        EASY = 1,
        MEDIUM = 2,
        HARD = 3,
    };
    mode m_mode;
    int prev_x, prev_y;
    int m_cellSize;
    int m_fieldSize;
    int m_delay;
    bool **m_map;
    QTimer m_timer;
    //QPainter *painter;

    void restartTimer();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:
    void slotUpdateMap();
    void slotStartTimer();
    void slotStopTimer();
    void slotClearMap();
    void slotChangeDelay(int delay_ms);

};

#endif // MAPWIDGET_H

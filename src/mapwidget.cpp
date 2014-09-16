#include "mapwidget.h"

#define LIVE_CELL Qt::green
#define DEAD_CELL Qt::black

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent)
{
    m_cellSize = 5;
    m_fieldSize = 150;
    m_mode = EASY;
    m_delay = 50;
    //painter = new QPainter(this);

    m_map = new bool*[m_fieldSize];
    for (int i =0; i < m_fieldSize; i++)
    {
        m_map[i] = new bool [m_fieldSize];
    }

    //slotClearMap();

    /*
    m_map[m_fieldSize / 2 + 1][m_fieldSize / 2 - 1] = true;
    m_map[m_fieldSize / 2 - 1][m_fieldSize / 2 - 1] = true;
    m_map[m_fieldSize / 2][m_fieldSize / 2] = true;
    m_map[m_fieldSize / 2 - 1][m_fieldSize / 2 + 1] = true;
    m_map[m_fieldSize / 2 + 1][m_fieldSize / 2 + 1] = true;
    */

    //m_timer = new QTimer(this);
    connect(&m_timer, SIGNAL(timeout()), SLOT(slotUpdateMap()));
    //m_timer.start(50);
}

QSize MapWidget::sizeHint() const
{
    return QSize(m_fieldSize * m_cellSize, m_fieldSize * m_cellSize);
}

QSize MapWidget::minimumSize() const
{
    return QSize(m_fieldSize * m_cellSize, m_fieldSize * m_cellSize);
}

QSize MapWidget::maximumSize() const
{
    return QSize(m_fieldSize * m_cellSize, m_fieldSize * m_cellSize);
}

void MapWidget::changeCellState(int x, int y)
{
    m_map[x][y] = m_map[x][y] ? false : true;
}

MapWidget::~MapWidget()
{
    for (int i = 0; i < m_fieldSize; i++)
    {
        delete[] m_map[i];
    }
    delete[] m_map;
}

//--------------------------------------SLOTS

void MapWidget::slotUpdateMap()
{
    int **matrix = new int*[m_fieldSize];
    for (int i = 0; i < m_fieldSize; i++)
    {
        matrix[i] = new int[m_fieldSize];
    }

    for (int i = 0; i < m_fieldSize; i++)
    {
        for (int j = 0; j < m_fieldSize; j++)
        {
            matrix[i][j] = 0;
        }
    }

    int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};

    for (int i = 0; i < m_fieldSize; i++)
    {
        for (int j = 0; j < m_fieldSize; j++)
        {
            //int nLiveCells = 0;
            for (int v = 0; v < 8; v++)
            {
                int x = j + dx[v], y = i + dy[v];
                if (j + dx[v] < 0)
                {
                    x = m_fieldSize + (j + dx[v]);
                }
                else if (j + dx[v] >= m_fieldSize)
                {
                    x = (j + dx[v]) - m_fieldSize;
                }
                if (i + dy[v] < 0)
                {
                    y = m_fieldSize + (i + dy[v]);
                }
                else if (i + dy[v] >= m_fieldSize)
                {
                    y = (i + dy[v]) - m_fieldSize;
                }
                /*
                if (((j + dx[v] > -1) && (j + dx[v] < m_fieldSize)) && ((i + dy[v] > -1) && (i + dy[v] < m_fieldSize)))
                {
                    if (m_map[i + dy[v]][j + dx[v]])
                    {
                        //nLiveCells++;
                        matrix[i][j]++;
                    }
                }
                */
                if (m_map[y][x])
                {
                    matrix[i][j]++;
                }
            }

            //matrix[i][j] = nLiveCells;

            /*
            if (nLiveCells == 3)
            {
                m_map[i][j] = true;
            }
            if (nLiveCells < 2 || nLiveCells > 3)
            {
                m_map[i][j] = false;
            }
            */
        }
    }

    for (int i = 0; i < m_fieldSize; i++)
    {
        for (int j = 0; j < m_fieldSize; j++)
        {
            if (matrix[i][j] == 3)
            {
                m_map[i][j] = true;
            }
            else if (!m_map[i][j] || matrix[i][j] != 2){
                m_map[i][j] = false;
            }
        }
    }

    for (int i = 0; i < m_fieldSize; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    update();

}

void MapWidget::slotStartTimer()
{
    m_timer.start(m_delay);
}

void MapWidget::slotStopTimer()
{
    m_timer.stop();
}

void MapWidget::slotClearMap()
{
    for (int i = 0; i < m_fieldSize; i++)
    {
        for (int j = 0; j < m_fieldSize; j++)
        {
            m_map[i][j] = false;
        }
    }

    update();
}

void MapWidget::slotChangeDelay(int delay_ms)
{
    m_delay = delay_ms;
    restartTimer();
}


//-----------------------------------------PROTECTED

void MapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(event->rect(), QBrush(Qt::darkGray));

    for (int i = 0; i < m_fieldSize; i++)
    {
        for (int j = 0; j < m_fieldSize; j++)
        {
            painter.fillRect(i * m_cellSize,
                                 j * m_cellSize,
                                 m_cellSize - m_cellSize / 20,
                                 m_cellSize - m_cellSize / 20,
                                 //m_map[i][j] ? QBrush(QPixmap("LiveCell_liveCell.png")) : QBrush(QPixmap("LiveCell_deadCell.png"))
                                 m_map[i][j] ? QBrush(LIVE_CELL) : QBrush(DEAD_CELL)
                                 );
        }
    }
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        changeCellState(event->x() / m_cellSize, event->y() / m_cellSize);
        update();
    }
    else
        QWidget::mousePressEvent(event);
}

/*
void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x() / m_cellSize, y = event->y() / m_cellSize;
    if (x != prev_x || y != prev_y)
    {
        m_map[prev_y][prev_x] == 0;
        if (x >= 0 && x < m_fieldSize && y >= 0 && y < m_fieldSize)
        {
            m_map[y][x] == 2;
        }
    }
    else
        QWidget::mouseMoveEvent(event);
}
*/

// ---------------------- PRIVATE

void MapWidget::restartTimer()
{
    m_timer.stop();
    m_timer.start(m_delay);
}


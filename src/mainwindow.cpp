#include "mainwindow.h"

MainWindow::MainWindow()
{
    QWidget *central = new QWidget;

    m_map.setMaximumSize(m_map.maximumSize());
    //m_controlPanel.setMaximumSize(m_controlPanel.maximumSize());

    QFrame *right_menu = new QFrame;
    QVBoxLayout *right_menu_lout = new QVBoxLayout;
    right_menu_lout->setAlignment(Qt::AlignTop);

    //    Timer Control
    QGroupBox *timer_control = new QGroupBox("Timer control");
    QPushButton *start_t = new QPushButton("start");
    connect(start_t, SIGNAL(clicked()), &m_map, SLOT(slotStartTimer()));
    QPushButton *stop_t = new QPushButton("stop");
    connect(stop_t, SIGNAL(clicked()), &m_map, SLOT(slotStopTimer()));
    QLabel *lbl = new QLabel("Delay (ms)");

    QSlider *slider_delay = new QSlider(Qt::Horizontal);
    slider_delay->setTickPosition(QSlider::TicksBelow);
    slider_delay->setTickInterval(50);
    slider_delay->setPageStep(50);
    slider_delay->setRange(50, 500);
    connect(slider_delay, SIGNAL(valueChanged(int)), &m_map, SLOT(slotChangeDelay(int)));
    QVBoxLayout *timer_lout = new QVBoxLayout;
    QHBoxLayout *timer_btn_lout = new QHBoxLayout;
    timer_btn_lout->addWidget(start_t);
    timer_btn_lout->addWidget(stop_t);
    timer_lout->addLayout(timer_btn_lout);
    timer_lout->addWidget(lbl);
    timer_lout->addWidget(slider_delay);
    timer_control->setLayout(timer_lout);
    timer_control->setMaximumSize(timer_control->sizeHint());

    //    Map control
    QGroupBox *map_control = new QGroupBox("Map control");
    QPushButton *clear_map = new QPushButton("clear map");
    connect(clear_map, SIGNAL(clicked()), &m_map, SLOT(slotClearMap()));
    QHBoxLayout *map_control_lout = new QHBoxLayout;
    map_control_lout->addWidget(clear_map);
    map_control->setLayout(map_control_lout);
    map_control->setMaximumSize((map_control->sizeHint()));

    right_menu_lout->addWidget(timer_control);
    right_menu_lout->addWidget(map_control);
    right_menu->setLayout(right_menu_lout);

    QHBoxLayout *lout = new QHBoxLayout;
    lout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    QScrollArea *scroll_map = new QScrollArea;
    scroll_map->setWidget(&m_map);
    lout->addWidget(scroll_map);
    lout->addWidget(right_menu);

    central->setLayout(lout);

    setCentralWidget(central);
    setWindowTitle("LiveCell");
}

MainWindow::~MainWindow()
{
}

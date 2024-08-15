#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paletteInit();
    timerInit();
}

void MainWindow::paletteInit(){
    ui->redSlider->setRange(0,255);
    ui->greenSlider->setRange(0,255);
    ui->blueSlider->setRange(0,255);
    ui->alphaSlider->setRange(0,255);
    ui->alphaSlider->setTickPosition(QSlider::TicksBelow);
    connect(ui->redSlider, &QSlider::valueChanged, this, &MainWindow::updateTextColor);
    connect(ui->greenSlider, &QSlider::valueChanged, this, &MainWindow::updateTextColor);
    connect(ui->blueSlider, &QSlider::valueChanged, this, &MainWindow::updateTextColor);
    connect(ui->alphaSlider, &QSlider::valueChanged, this, &MainWindow::updateTextColor);
}
void MainWindow::updateTextColor(){
    int red = ui->redSlider->value();
    int green = ui->greenSlider->value();
    int blue = ui->blueSlider->value();
    int alpha = ui->alphaSlider->value();
    QColor color(red, green, blue, alpha);
    QPalette p = ui->colorTextEdit->palette();
    p.setColor(QPalette::Base, color);
    ui->colorTextEdit->setPalette(p);
}

void MainWindow::timerInit(){
    ui->timeProgressBar->setValue(0);
    my_timer=new QTimer();
    my_timer->setInterval(1000);
    my_timer->stop();
    ui->msecSpinBox->setRange(0,1000);
    connect(ui->startButton,&QPushButton::clicked,this,[&](){
        time_status=true;
        last_time=QDateTime::currentDateTime();
        ui->minLcdNumber->display(0);
        ui->secLcdNumber->display(0);
        ui->msecLcdNumber->display(0);
        my_timer->start();
    });
    connect(ui->stopButton,&QPushButton::clicked,this,[&](){
        time_status=false;
        my_timer->stop();
    });
    connect(my_timer,&QTimer::timeout,this,&MainWindow::updateCld);
    connect(ui->timeSetButton,&QPushButton::clicked,this,[&](){
        int space = ui->msecSpinBox->value();
        my_timer->setInterval(space);
    });
}

void MainWindow::updateCld(){
    QDateTime cur_time = QDateTime::currentDateTime();
    int elapsed_ms = last_time.msecsTo(cur_time);
    int min = elapsed_ms / 1000 / 60;
    int sec = elapsed_ms / 1000 % 60;
    int msec = elapsed_ms % 1000;
    int val = elapsed_ms / 600;
    ui->minLcdNumber->display(min);
    ui->secLcdNumber->display(sec);
    ui->msecLcdNumber->display(msec);
    ui->timeProgressBar->setValue(val);
}

MainWindow::~MainWindow()
{
    delete ui;
}

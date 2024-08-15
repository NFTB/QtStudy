#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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


MainWindow::~MainWindow()
{
    delete ui;
}

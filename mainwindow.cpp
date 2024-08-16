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

void MainWindow::on_listIniButton_clicked()
{
    QListWidgetItem *aItem;
    bool chk=ui->editCheckBox->isChecked();
    ui->listWidget->clear();
    for(int i=0;i<10;++i){
        QString str=QString::asprintf("Item %d",i);
        aItem=new QListWidgetItem();
        aItem->setText(str);
        aItem->setCheckState(Qt::Checked);
        if(chk){
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable
                           |Qt::ItemIsEnabled|Qt::ItemIsEditable);
        }else{
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable
                            |Qt::ItemIsEnabled);
        }
        ui->listWidget->addItem(aItem);
    }
}


void MainWindow::on_insertButton_clicked()
{
    bool chk=ui->editCheckBox->isChecked();
    QListWidgetItem *aItem=new QListWidgetItem("New inserted Item");
    aItem->setCheckState(Qt::Checked);
    if(chk){
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable
                        |Qt::ItemIsEnabled|Qt::ItemIsEditable);
    }else{
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable
                        |Qt::ItemIsEnabled);
    }
    ui->listWidget->insertItem(ui->listWidget->currentRow(),aItem);
}


void MainWindow::on_clearButton_clicked()
{
    ui->listWidget->clear();
}


void MainWindow::on_delButton_clicked()
{
    int row=ui->listWidget->currentRow();
    QListWidgetItem* aItem=ui->listWidget->takeItem(row);
    delete aItem;
}


void MainWindow::on_addButton_clicked()
{
    bool chk=ui->editCheckBox->isChecked();
    QListWidgetItem *aItem=new QListWidgetItem("New inserted Item");
    aItem->setCheckState(Qt::Checked);
    if(chk){
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable
                        |Qt::ItemIsEnabled|Qt::ItemIsEditable);
    }else{
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable
                        |Qt::ItemIsEnabled);
    }
    ui->listWidget->addItem(aItem);
}


void MainWindow::on_allSelectButton_clicked()
{
    int cnt=ui->listWidget->count();
    for(int i=0;i<cnt;++i){
        QListWidgetItem *aItem=ui->listWidget->item(i);
        aItem->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_allNotSelectButton_clicked()
{
    int cnt=ui->listWidget->count();
    for(int i=0;i<cnt;++i){
        QListWidgetItem *aItem=ui->listWidget->item(i);
        aItem->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_revSelectButton_clicked()
{
    int cnt=ui->listWidget->count();
    for(int i=0;i<cnt;++i){
        QListWidgetItem *aItem=ui->listWidget->item(i);
        if(aItem->checkState()==Qt::Checked){
            aItem->setCheckState(Qt::Unchecked);
        }else{
            aItem->setCheckState(Qt::Checked);
        }
    }
}


void MainWindow::on_editCheckBox_stateChanged(int arg1)
{
    int cnt=ui->listWidget->count();
    for(int i=0;i<cnt;++i){
        QListWidgetItem *aItem=ui->listWidget->item(i);
        if(arg1==Qt::Checked){
            aItem->setFlags(aItem->flags()|Qt::ItemIsEditable);
        }else{
            aItem->setFlags(aItem->flags()^Qt::ItemIsEditable);
        }
    }
}


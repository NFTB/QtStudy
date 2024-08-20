#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    paletteInit();
    timerInit();
    ui->View->keyPress(nullptr);
    // connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &MainWindow::onStackedWidgetPageChanged);
    if (ui->stackedWidget->currentIndex() == 1) {
        drawInit();
    }
}

void MainWindow::drawInit(){
    labViewCord=new QLabel("View 坐标：");
    labViewCord->setMinimumWidth(150);
    ui->statusBar->addWidget(labViewCord);

    labSceneCord=new QLabel("Scene 坐标：");
    labSceneCord->setMinimumWidth(150);
    ui->statusBar->addWidget(labSceneCord);

    labItemCord=new QLabel("Item 坐标：");
    labItemCord->setMinimumWidth(150);
    ui->statusBar->addWidget(labItemCord);

    labItemInfo=new QLabel("ItemInfo: ");
    labItemInfo->setMinimumWidth(200);
    ui->statusBar->addWidget(labItemInfo);

    scene=new QGraphicsScene(-300,-200,600,200);

    ui->View->setScene(scene);

    ui->View->setCursor(Qt::CrossCursor);
    ui->View->setMouseTracking(true);
    ui->View->setDragMode(QGraphicsView::RubberBandDrag);

    this->setCentralWidget(ui->View);

    connect(ui->View,SIGNAL(mouseMovePoint(QPoint)),
                     this, SLOT(on_mouseMovePoint(QPoint)));

    connect(ui->View,SIGNAL(mouseClicked(QPoint)),
                     this, SLOT(on_mouseClicked(QPoint)));

    connect(ui->View,SIGNAL(mouseDoubleClick(QPoint)),
                     this, SLOT(on_mouseDoubleClick(QPoint)));

    connect(ui->View,SIGNAL(keyPress(QKeyEvent*)),
                     this, SLOT(on_keyPress(QKeyEvent*)));
}

void MainWindow::resetDrawPage(){
    ui->statusBar->removeWidget(labViewCord);
    ui->statusBar->removeWidget(labSceneCord);
    ui->statusBar->removeWidget(labItemCord);
    ui->statusBar->removeWidget(labItemInfo);
    scene->clear();
    ui->View->setCursor(Qt::ArrowCursor);
    ui->View->setMouseTracking(false);
    ui->View->setDragMode(QGraphicsView::NoDrag);
    disconnect(ui->View, SIGNAL(mouseMovePoint(QPoint)), this, SLOT(on_mouseMovePoint(QPoint)));
    disconnect(ui->View, SIGNAL(mouseClicked(QPoint)), this, SLOT(on_mouseClicked(QPoint)));
    disconnect(ui->View, SIGNAL(mouseDoubleClick(QPoint)), this, SLOT(on_mouseDoubleClick(QPoint)));
    disconnect(ui->View, SIGNAL(keyPress(QKeyEvent*)), this, SLOT(on_keyPress(QKeyEvent*)));
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

void MainWindow::paintEvent(QPaintEvent *)
{
    return;
    if(ui->stackedWidget->currentIndex()!=0){

        return;
    }
    QPainter painter(this);
    int W=width();
    int pos=ui->groupBox_5->y()+ui->groupBox_5->height();
    int H=height()-pos;
    int side=qMin(W,H);
    QRect rect(0,pos+(H-side)/2,side,side);
    painter.drawRect(rect);
    painter.setViewport(rect);
    painter.setWindow(-100,-100,200,200);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    for(int i=0;i<36;++i){
        painter.drawEllipse(QPoint(50,0),50,50);
        painter.rotate(10);
    }
}

void MainWindow::onStackedWidgetPageChanged(int index){
    if(index==1){
        drawInit();
    }else if(index==0){
        resetDrawPage();
    }
}

int MainWindow::getRand(int l,int r){
    int len=r-l+1;
    int res=l+ QRandomGenerator::global()->bounded(len);
    return res;
}

void MainWindow::on_mouseMovePoint(QPoint point){
    labViewCord->setText(QString::asprintf("View 坐标: %d %d",point.x(),point.y()));
    QPointF pointScene=ui->View->mapToScene(point);
    labSceneCord->setText(QString::asprintf("Secen 坐标: %.0f,%.0f",pointScene.x(),pointScene.y()));
}

void MainWindow::on_mouseClicked(QPoint point){
    QPointF pointScene=ui->View->mapToScene(point);
    QGraphicsItem *item=NULL;
    item=scene->itemAt(pointScene,ui->View->transform());
    if(item!=NULL){
        QPointF pointItem=item->mapFromScene(pointScene);
        labItemCord->setText(QString::asprintf("Item 坐标：%.0f,%.0f",pointItem.x(),pointItem.y()));
        labItemInfo->setText(item->data(ItemDesciption).toString()+", ItemId="+
                             item->data(ItemId).toString());
    }
}

template<typename T> void setBrushColor(T *item){
    QColor color=item->brush().color();
    color=QColorDialog::getColor(color,NULL,"选择填充颜色");
    if(color.isValid()){
        item->setBrush(QBrush(color));
    }
}
void MainWindow::on_mouseDoubleClick(QPoint point){
    QPointF pointScene=ui->View->mapToScene(point);
    QGraphicsItem  *item=NULL;
    item=scene->itemAt(pointScene,ui->View->transform());
    if (item == NULL){
        return;
    }
    switch (item->type()){
        case QGraphicsRectItem::Type:{
        QGraphicsRectItem *theItem=qgraphicsitem_cast<QGraphicsRectItem*>(item);
            setBrushColor(theItem);
            break;
        }
        case QGraphicsEllipseItem::Type:{
            QGraphicsEllipseItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            setBrushColor(theItem);
            break;
        }

        case QGraphicsPolygonItem::Type:{
            QGraphicsPolygonItem *theItem=qgraphicsitem_cast<QGraphicsPolygonItem*>(item);
            setBrushColor(theItem);
            break;
        }
        case QGraphicsLineItem::Type:{
            QGraphicsLineItem *theItem=qgraphicsitem_cast<QGraphicsLineItem*>(item);
            QPen    pen=theItem->pen();
            QColor  color=theItem->pen().color();
            color=QColorDialog::getColor(color,this,"选择线条颜色");
            if (color.isValid()){
                pen.setColor(color);
                theItem->setPen(pen);
            }
            break;
        }
        case QGraphicsTextItem::Type:{
            QGraphicsTextItem *theItem=qgraphicsitem_cast<QGraphicsTextItem*>(item);
            QFont font=theItem->font();
            bool ok=false;
            font=QFontDialog::getFont(&ok,font,this,"设置字体");
            if (ok){
                theItem->setFont(font);
            }
            break;
        }
    }
}

void MainWindow::on_keyPress(QKeyEvent *event){
    if (scene->selectedItems().count()!=1){
        return;
    }
    QGraphicsItem *item=scene->selectedItems().at(0);

    if (event->key()==Qt::Key_Delete){
        scene->removeItem(item);
    }
    else if (event->key()==Qt::Key_Space){
        item->setRotation(90+item->rotation());
    }
    else if (event->key()==Qt::Key_PageUp){
        item->setScale(0.1+item->scale());
    }
    else if (event->key()==Qt::Key_PageDown){
        item->setScale(-0.1+item->scale());
    }
    else if (event->key()==Qt::Key_Left){
        item->setX(-1+item->x());
    }
    else if (event->key()==Qt::Key_Right){
        item->setX(1+item->x());
    }
    else if (event->key()==Qt::Key_Up){
        item->setY(-1+item->y());
    }
    else if (event->key()==Qt::Key_Down){
        item->setY(1+item->y());
    }
}

void MainWindow::on_actItem_Rect_triggered()
{
    QGraphicsRectItem   *item=new QGraphicsRectItem(-50,-25,100,50);
    item->setFlags(QGraphicsItem::ItemIsMovable
                   | QGraphicsItem::ItemIsSelectable
                   | QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::yellow));
    item->setZValue(++frontZ);
    item->setPos(-50+(getRand(0,100)),-50+(getRand(0,100)));
    item->setData(ItemId,++seqNum);
    item->setData(ItemDesciption,"矩形");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void MainWindow::on_actItem_Ellipse_triggered()
{
    QRandomGenerator::global()->bounded(40001);
    QGraphicsEllipseItem *item=new QGraphicsEllipseItem(-50,-30,100,60);
    item->setFlags(QGraphicsItem::ItemIsMovable
                   | QGraphicsItem::ItemIsSelectable
                   | QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::blue));
    item->setZValue(++frontZ);
    item->setPos(-50+(getRand(0,100)),-50+(getRand(0,100)));
    item->setData(ItemId,++seqNum);
    item->setData(ItemDesciption,"椭圆");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}


void MainWindow::on_actItem_Circle_triggered()
{
    QGraphicsEllipseItem *item=new QGraphicsEllipseItem(-50,-50,100,100);
    item->setFlags(QGraphicsItem::ItemIsMovable
                   | QGraphicsItem::ItemIsSelectable
                   | QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::cyan));
    item->setZValue(++frontZ);
    item->setPos(-50+(getRand(0,100)),-50+(getRand(0,100)));
    item->setData(ItemId,++seqNum);
    item->setData(ItemDesciption,"圆形");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}


void MainWindow::on_actItem_Triangle_triggered()
{
    QGraphicsPolygonItem *item=new QGraphicsPolygonItem;
    QPolygonF points;
    points.append(QPointF(0,-40));
    points.append(QPointF(60,40));
    points.append(QPointF(-60,40));
    item->setPolygon(points);
    item->setPos(-50+(getRand(0,100)),-50+(getRand(0,100)));
    item->setFlags(QGraphicsItem::ItemIsMovable
                   | QGraphicsItem::ItemIsSelectable
                   | QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::magenta));
    item->setZValue(++frontZ);
    item->setData(ItemId,++seqNum);
    item->setData(ItemDesciption,"三角形");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}


void MainWindow::on_actItem_Polygon_triggered()
{
    QGraphicsPolygonItem *item=new QGraphicsPolygonItem;
    QPolygonF points;
    points.append(QPointF(-40,-40));
    points.append(QPointF(40,-40));
    points.append(QPointF(100,40));
    points.append(QPointF(-100,40));
    item->setPolygon(points);
    item->setPos(-50+(getRand(0,100)),-50+(getRand(0,100)));
    item->setFlags(QGraphicsItem::ItemIsMovable
                   | QGraphicsItem::ItemIsSelectable
                   | QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::green));
    item->setZValue(++frontZ);
    item->setData(ItemId,++seqNum);
    item->setData(ItemDesciption,"梯形");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}


void MainWindow::on_actItem_Line_triggered()
{
    QGraphicsLineItem *item=new QGraphicsLineItem(-100,0,100,0);
    item->setFlags(QGraphicsItem::ItemIsMovable
                   | QGraphicsItem::ItemIsSelectable
                   | QGraphicsItem::ItemIsFocusable);
    QPen pen(Qt::red);
    pen.setWidth(3);
    item->setPen(pen);
    item->setZValue(++frontZ);
    item->setPos(-50+(getRand(0,100)),-50+(getRand(0,100)));
    item->setData(ItemId,++seqNum);
    item->setData(ItemDesciption,"直线");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}


void MainWindow::on_actItem_Text_triggered()
{
    QString str=QInputDialog::getText(this,"输入文字","请输入文字");
    if (str.isEmpty()){
        return;
    }
    QGraphicsTextItem *item=new QGraphicsTextItem(str);
    QFont font=this->font();
    font.setPointSize(20);
    font.setBold(true);
    item->setFont(font);
    item->setFlags(QGraphicsItem::ItemIsMovable
                   | QGraphicsItem::ItemIsSelectable
                   | QGraphicsItem::ItemIsFocusable);
    item->setPos(-50+(getRand(0,100)),-50+(getRand(0,100)));
    item->setZValue(++frontZ);
    item->setData(ItemId,++seqNum);
    item->setData(ItemDesciption,"文字");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}


void MainWindow::on_actZoomIn_triggered()
{
    int cnt=scene->selectedItems().count();
    if (cnt==0){
        ui->View->scale(1.1,1.1);
    }
    else{
        for(int i=0;i<cnt;++i){
            QGraphicsItem *item;
            item=scene->selectedItems().at(i);
            item->setScale(0.1+item->scale());
        }
    }
}


void MainWindow::on_actZoomOut_triggered()
{
    int cnt=scene->selectedItems().count();
    if (cnt==0){
        ui->View->scale(0.9,0.9);
    }
    else{
        for(int i=0;i<cnt;++i){
            QGraphicsItem *item;
            item=scene->selectedItems().at(i);
            item->setScale(item->scale()-0.1);
        }
    }
}


void MainWindow::on_actRestore_triggered()
{
    int cnt=scene->selectedItems().count();
    if (cnt==0){
        ui->View->resetTransform();
    }
    else{
        for(int i=0;i<cnt;++i){
            QGraphicsItem* item=scene->selectedItems().at(i);
            item->setRotation(0);
            item->setScale(1.0);
        }
    }
}


void MainWindow::on_actRotateLeft_triggered()
{
    int cnt=scene->selectedItems().count();
    if (cnt==0){
        ui->View->rotate(-30);
    }
    else{
        for(int i=0;i<cnt;++i){
            QGraphicsItem* item=scene->selectedItems().at(i);
            item->setRotation(-30+item->rotation());
        }
    }
}



void MainWindow::on_actRotateRight_triggered()
{
    int cnt=scene->selectedItems().count();
    if (cnt==0){
        ui->View->rotate(+30);
    }
    else{
        for(int i=0;i<cnt;++i){
            QGraphicsItem* item=scene->selectedItems().at(i);
            item->setRotation(+30+item->rotation());
        }
    }
}


void MainWindow::on_actEdit_Front_triggered()
{
    int cnt=scene->selectedItems().count();
    if (cnt>0){
        QGraphicsItem* item=scene->selectedItems().at(0);
        item->setZValue(++frontZ);
    }
}


void MainWindow::on_actEdit_Back_triggered()
{
    int cnt=scene->selectedItems().count();
    if (cnt>0){
        QGraphicsItem* item=scene->selectedItems().at(0);
        item->setZValue(--backZ);
    }
}



void MainWindow::on_actGroup_triggered()
{
    int cnt=scene->selectedItems().count();
    if (cnt>1){
        QGraphicsItemGroup* group =new QGraphicsItemGroup;
        scene->addItem(group);
        for (int i=0;i<cnt;i++){
            QGraphicsItem* item=scene->selectedItems().at(0);
            item->setSelected(false);
            item->clearFocus();
            group->addToGroup(item);
        }
        group->setFlags(QGraphicsItem::ItemIsMovable
                        | QGraphicsItem::ItemIsSelectable
                        | QGraphicsItem::ItemIsFocusable);

        group->setZValue(++frontZ);
        scene->clearSelection();
        group->setSelected(true);
    }
}


void MainWindow::on_actGroupBreak_triggered()
{
    int cnt=scene->selectedItems().count();
    if (cnt==1){
        QGraphicsItemGroup  *group;
        group=(QGraphicsItemGroup*)scene->selectedItems().at(0);
        scene->destroyItemGroup(group);
    }
}


void MainWindow::on_actEdit_Delete_triggered()
{
    int cnt=scene->selectedItems().count();
    if (cnt>0){
        for (int i=0;i<cnt;i++){
            QGraphicsItem*  item=scene->selectedItems().at(0);
            scene->removeItem(item);
        }
    }
}


void MainWindow::on_actQuit_triggered()
{
    return;
}


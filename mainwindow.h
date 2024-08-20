#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QListWidgetItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QLabel>
#include <QRandomGenerator>
#include <QGraphicsEllipseItem>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_mouseMovePoint(QPoint point);
    void on_mouseClicked(QPoint point);
    void on_mouseDoubleClick(QPoint point);
    void on_keyPress(QKeyEvent *event);
    void on_listIniButton_clicked();
    void on_insertButton_clicked();
    void on_clearButton_clicked();
    void on_delButton_clicked();
    void on_addButton_clicked();
    void on_allSelectButton_clicked();
    void on_revSelectButton_clicked();
    void on_allNotSelectButton_clicked();
    void on_editCheckBox_stateChanged(int arg1);
    void on_actItem_Rect_triggered();
    void on_actItem_Ellipse_triggered();

    void on_actItem_Circle_triggered();

    void on_actItem_Triangle_triggered();

    void on_actItem_Polygon_triggered();

    void on_actItem_Line_triggered();

    void on_actItem_Text_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actRestore_triggered();

    void on_actRotateLeft_triggered();

    void on_actRotateRight_triggered();

    void on_actEdit_Front_triggered();

    void on_actEdit_Back_triggered();

    void on_actGroup_triggered();

    void on_actGroupBreak_triggered();

    void on_actEdit_Delete_triggered();

    void on_actQuit_triggered();

private:
    void paletteInit();
    void updateTextColor();
    void timerInit();
    void updateCld();
    void paintEvent(QPaintEvent *);
    int getRand(int l,int r);
    void drawInit();
    void resetDrawPage();
    void onStackedWidgetPageChanged(int index);
private:
    Ui::MainWindow *ui;
    QTimer *my_timer;
    QDateTime last_time;
    bool time_status;
    static const int ItemId =1;
    static const int ItemDesciption=2;
    int seqNum=0;
    int frontZ=0;
    int backZ=0;
    QGraphicsScene *scene;
    QLabel *labViewCord;
    QLabel *labSceneCord;
    QLabel *labItemCord;
    QLabel *labItemInfo;

};
#endif // MAINWINDOW_H

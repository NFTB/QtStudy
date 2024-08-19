#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QListWidgetItem>
#include <QPainter>


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
    void on_listIniButton_clicked();

    void on_insertButton_clicked();

    void on_clearButton_clicked();

    void on_delButton_clicked();

    void on_addButton_clicked();

    void on_allSelectButton_clicked();

    void on_revSelectButton_clicked();

    void on_allNotSelectButton_clicked();

    void on_editCheckBox_stateChanged(int arg1);

private:
    void paletteInit();
    void updateTextColor();
    void timerInit();
    void updateCld();
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    QTimer *my_timer;
    QDateTime last_time;
    bool time_status;
};
#endif // MAINWINDOW_H

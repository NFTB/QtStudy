#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>


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

private:
    void paletteInit();
    void updateTextColor();
    void timerInit();
    void updateCld();
private:
    Ui::MainWindow *ui;
    QTimer *my_timer;
    QDateTime last_time;
    bool time_status;
};
#endif // MAINWINDOW_H

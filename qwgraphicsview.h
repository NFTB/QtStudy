#ifndef QWGRAPHICSVIEW_H
#define QWGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>


class QWGraphicsView:public QGraphicsView
{
    Q_OBJECT
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
public:
    QWGraphicsView(QWidget *parent=0);
signals:
    void mouseMovePoint(QPoint point);
    void mouseClicked(QPoint point);
    void mouseDoubleClick(QPoint point);
    void keyPress(QKeyEvent *event);
};

#endif // QWGRAPHICSVIEW_H

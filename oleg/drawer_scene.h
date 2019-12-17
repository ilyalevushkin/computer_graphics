#ifndef DRAWER_SCENE_H
#define DRAWER_SCENE_H

#include <QWidget>
#include <QPainter>

class Drawer_Scene : public QWidget
{
    Q_OBJECT
public:
    explicit Drawer_Scene(QWidget *parent = nullptr);
    void loadImage(QImage &img);
signals:

public slots:

private:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    QImage *image;
};

#endif // DRAWER_SCENE_H

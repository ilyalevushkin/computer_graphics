#include "drawer_scene.h"

Drawer_Scene::Drawer_Scene(QWidget *parent) : QWidget(parent)
{
    image = new QImage(this->size(), QImage::Format_RGB32);
    image->fill(Qt::white);
}




void Drawer_Scene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    //image->fill(Qt::white);
    //image->setPixel(0, 0, 0xffffff);
    QPixmap pixmap = QPixmap::fromImage(*image);
    painter.drawPixmap(this->rect(), pixmap);
}

void Drawer_Scene::resizeEvent(QResizeEvent *) {
    if (image)
        delete image;
    image = new QImage(this->size(), QImage::Format_RGB32);
    image->fill(Qt::white);
}

void Drawer_Scene::loadImage(QImage &img)
{
    if (image)
        delete image;
    image = new QImage(img);
}

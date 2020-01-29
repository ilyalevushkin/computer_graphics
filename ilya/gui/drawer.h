#ifndef DRAWER_H
#define DRAWER_H

#include <QGraphicsScene>
#include <QPainter>
#include "../object/color.h"
#include <iostream>
#include "../drawer_scene.h"
#include <math.h>

#include "../lighting.h"

class BaseDrawer
{
public:
    BaseDrawer() = default;
    virtual ~BaseDrawer() = default;

    virtual void draw() = 0;

    virtual void addPoint(const int x, const int y, rgb_color color) = 0;



    virtual void addLine(int xB, int yB, int xE,
                          int yE, rgb_color) = 0;

    virtual Point getLighting() = 0;

    virtual void setLighting(Point l) = 0;

    virtual double getIntensity() = 0;

    virtual void setIntensity(double intensity) = 0;

    virtual QColor getColor() = 0;
};

class ModelDrawer : public BaseDrawer
{
public:
    ModelDrawer(Drawer_Scene* canvas, Point l, double intensity, QColor clr) : BaseDrawer(), canvas(canvas), clr(clr) {
        if (fabs(get_length(l) - 1) < 0.00001)
        {
            this->l = l;
        }
        else
        {
            this->l = {0,0,1};
        }
        if (intensity < 0)
        {
            this->intensity = 1;
        }
        else
        {
            this->intensity = intensity;
        }
        img = new QImage(canvas->size(), QImage::Format_RGB32);
        img->fill(clr);
    }
    ~ModelDrawer() override = default;


    void addPoint(const int x, const int y, rgb_color color) override
    {
        img->setPixel(x, y, QColor(color.red,color.green,color.blue).rgb());
    }

    void addLine(int x1, int y1, int x2,
                              int y2, rgb_color color) override
    {
        //x1 += 350;
        //x2 += 350;
        //y1 += 350;
        //y2 += 350;
        if (x1 > 700 || x2 > 700 || x1 < 0 || x2 < 0 ||
                y1 > 700 || y2 > 700 || y1 < 0 || y2 < 0)
        {
            return;
        }
        uint clr = QColor(color.red,color.green,color.blue).rgb();
        const int deltaX = abs(x2 - x1);
        const int deltaY = abs(y2 - y1);
        const int signX = x1 < x2 ? 1 : -1;
        const int signY = y1 < y2 ? 1 : -1;

        int error = deltaX - deltaY;

        img->setPixel(x2, y2, clr);
        while(x1 != x2 || y1 != y2)
        {
            img->setPixel(x1, y1, clr);
            const int error2 = error * 2;
            //
            if(error2 > -deltaY)
            {
                error -= deltaY;
                x1 += signX;
            }
            if(error2 < deltaX)
            {
                error += deltaX;
                y1 += signY;
            }
        }
    }

    double getIntensity() override
    {
        return intensity;
    }

    void setIntensity(double intensity) override
    {
        if (intensity < 0)
        {
            this->intensity = 1;
        }
        else
        {
            this->intensity = intensity;
        }
    }

    Point getLighting() override
    {
        return l;
    }

    void setLighting(Point l) override
    {
        if (fabs(get_length(l) - 1) < 0.00001)
        {
            this->l = l;
        }
    }

    void draw() override
    {
        canvas->loadImage(*img);
        canvas->update();
    }

    QColor getColor() override
    {
        return clr;
    }

private:

    double get_length(Point v)
    {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    Drawer_Scene *canvas;
    QImage *img;
    QColor clr;
    Point l;
    double intensity;
};

#endif // DRAWER_H

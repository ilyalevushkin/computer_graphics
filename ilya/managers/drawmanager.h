#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include "gui/drawer.h"
#include "object/compositeobject.h"
#include "../object/transformed_model.h"
#include "exceptions/drawerException.h"
#include "../z-bufer/z_buffer.h"

#include <stdlib.h>
#include <x86intrin.h>

#include <armadillo>

#include "../lighting.h"

using namespace std;
using namespace arma;

class DrawManager
{
public:
    DrawManager() = default;
    ~DrawManager() = default;

    void drawcolorfulModel(BaseDrawer &drw, std::shared_ptr<Object> mod, std::shared_ptr<Object> camera);
    void drawWhiteList(BaseDrawer& drw);

private:
    void print_coords_axes(shared_ptr<Camera> cm, vector<Point> &coords);
    static constexpr double coeff3D = 0.5;

    int getX(const double x, const double z) const;
    int getY(const double y, const double z) const;
};

#endif // DRAWMANAGER_H

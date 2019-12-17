#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include "gui/drawer.h"
#include "object/compositeobject.h"
#include "../object/transformed_model.h"
#include "exceptions/drawerException.h"
#include "../z-bufer/z_buffer.h"

#include "../lighting.h"

using namespace std;

class DrawManager
{
public:
    DrawManager() = default;
    ~DrawManager() = default;

    void drawModel(BaseDrawer &drw, const ObjIter& b, const ObjIter& e, \
                   std::shared_ptr<Object> obj);
    void drawcolorfulModel(BaseDrawer &drw, const ObjIter& b, const ObjIter& e, \
                   std::shared_ptr<Object> obj);

private:
    void print_coords_axes(shared_ptr<Camera> cm, vector<Point> &coords);
    static constexpr double coeff3D = 0.5;

    int getX(const double x, const double z) const;
    int getY(const double y, const double z) const;
};

#endif // DRAWMANAGER_H

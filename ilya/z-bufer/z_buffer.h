#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include "../object/triangle.h"
#include "../object/color.h"
#include "../gui/drawer.h"
#include "../object/color.h"
#include "../lighting.h"

#define MAXDIST 10000

#include <vector>

using namespace std;

typedef struct Point3d POINT3D;
typedef struct Cell CELL;

//Структура для точки в 3-мерном пространстве.
struct Point3d {
    double x, y, z;
};

//Структура ячейки, из которых будет состоять Z-буфер.
struct Cell {
    double z;
    rgb_color color;
};


//Класс Z-буфера.
class ZBuffer {
    public:
        ZBuffer ( size_t, size_t );
        ~ZBuffer () = default;
        void PutTriangle(Triangle&);
        void PutAxes(Point A, Point B, rgb_color clr);
        void Show(BaseDrawer &drw);
        void Clear(rgb_color clr);
    private:
       void z_buf_check(int point[3], rgb_color clr);
       size_t sX, sY;	// Размер Z-Буфера
       vector<vector<Cell>> buf;
};


#endif // Z_BUFFER_H

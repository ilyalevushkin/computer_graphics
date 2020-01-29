#ifndef Z_BUFFER_CPP
#define Z_BUFFER_CPP


#include "z_buffer.h"


//Конструктор Z-буфера.
ZBuffer :: ZBuffer ( size_t ax, size_t ay ) : sX(ax), sY(ay), buf(ay) {
    for (size_t i = 0; i < ay; i++)
    {
        buf[i] = vector<Cell>(ax);
    }
}


//Функция, выводящая на экран содержимое заполненного Z-буфера.
void ZBuffer :: Show(BaseDrawer &drw) {
    for (size_t j = 0; j < sY; j++)
    {
        for (size_t i = 0; i < sX; i++)
        {
            //Выводим пиксели на экран
            drw.addPoint(int(i), int(j), buf[j][i].color);
        }
    }
    drw.draw();
}

//Функция, 'очищающая' Z-буфер.
void ZBuffer :: Clear (rgb_color clr) {
    for (size_t j = 0; j < sY; j++)
    {
        for (size_t i = 0; i < sX; i++)
        {
            //Инициализируем ячейки Z-буфера
            buf[j][i].z = MAXDIST;
            buf[j][i].color = clr;
        }
    }
}

void check_rgb(int &rgb)
{
    if (rgb < 0)
    {
        rgb = 0;
    }
    if (rgb > 255)
    {
        rgb = 255;
    }
}

void color_check(rgb_color &clr)
{
    check_rgb(clr.red);
    check_rgb(clr.green);
    check_rgb(clr.blue);
}


rgb_color multiply_color(rgb_color clr, double a)
{
    return {int(clr.red * a), int(clr.green * a), int(clr.blue * a)};
}

rgb_color sum_color(rgb_color clr, rgb_color clr2)
{
    return {clr.red + clr2.red, clr.green + clr2.green, clr.blue + clr2.blue};
}


void ZBuffer::z_buf_check(int point[3], rgb_color clr)
{
    if (point[0] >= 700 || point[0] < 0 || point[1] < 0 || point[1] >= 700)
    {
        return;
    }

    if (point[2] < buf[point[1]][point[0]].z)
    {
        buf[point[1]][point[0]].z = point[2];
        buf[point[1]][point[0]].color = clr;
    }
}

void ZBuffer::PutAxes(Point A, Point B, rgb_color clr)
{
    int x1 = int(A.x);
    int x2 = int(B.x);
    int y1 = int(A.y);
    int y2 = int(B.y);
    int z1 = int(A.z);
    int z2 = int(B.z);
    int i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
    int point[3];

    point[0] = x1;
    point[1] = y1;
    point[2] = z1;
    dx = x2 - x1;
    dy = y2 - y1;
    if (dx == 0 && dy == 0)
    {
        return;
    }
    dz = z2 - z1;
    x_inc = (dx < 0) ? -1 : 1;
    l = abs(dx);
    y_inc = (dy < 0) ? -1 : 1;
    m = abs(dy);
    z_inc = (dz < 0) ? -1 : 1;
    n = abs(dz);
    dx2 = l << 1;
    dy2 = m << 1;
    dz2 = n << 1;

    if ((l >= m) && (l >= n))
    {
        err_1 = dy2 - l;
        err_2 = dz2 - l;
        while (point[0] < 700 && point[0] >= 0 && point[1] >= 0 && point[1] < 700)
        {
            z_buf_check(point, clr);
            if (err_1 > 0) {
                point[1] += y_inc;
                err_1 -= dx2;
            }
            if (err_2 > 0) {
                point[2] += z_inc;
                err_2 -= dx2;
            }
            err_1 += dy2;
            err_2 += dz2;
            point[0] += x_inc;
        }
    }
    else if ((m >= l) && (m >= n))
    {
        err_1 = dx2 - m;
        err_2 = dz2 - m;
        while (point[0] < 700 && point[0] >= 0 && point[1] >= 0 && point[1] < 700)
        {
            z_buf_check(point, clr);
            if (err_1 > 0) {
                point[0] += x_inc;
                err_1 -= dy2;
            }
            if (err_2 > 0) {
                point[2] += z_inc;
                err_2 -= dy2;
            }
            err_1 += dx2;
            err_2 += dz2;
            point[1] += y_inc;
        }
    }
    else
    {
        err_1 = dy2 - n;
        err_2 = dx2 - n;
        while (point[0] < 700 && point[0] >= 0 && point[1] >= 0 && point[1] < 700)
        {
            z_buf_check(point, clr);
            if (err_1 > 0) {
                point[1] += y_inc;
                err_1 -= dz2;
            }
            if (err_2 > 0) {
                point[0] += x_inc;
                err_2 -= dz2;
            }
            err_1 += dy2;
            err_2 += dx2;
            point[2] += z_inc;
        }
    }
    z_buf_check(point, clr);
}

void get_IR_IQ(rgb_color &IR, rgb_color &IQ, Node A, Node B, Node C, double y)
{
    double u, w;
    double AQ, QB, CR, RB;
    rgb_color IA, IB, IC;
    IA = A.getcolor();
    IB = B.getcolor();
    IC = C.getcolor();
    AQ = C.getY() - y;
    QB = C.getY() - A.getY();

    if (QB < 1)
    {
        IR = IA;
        IQ = IA;
    }
    if (AQ < 1)
    {
        IR = IC;
        IQ = IC;
    }

    u = AQ / QB;
    IQ = sum_color(multiply_color(IC, u), multiply_color(IA, 1 - u));


    if (y < B.getY())
    {
        CR = B.getY() - y;
        RB = QB;
        if (CR < 1)
        {
            IR = IB;
            IQ = IB;
        }
        w = CR / RB;
        IR = sum_color(multiply_color(IB, w), multiply_color(IA, 1 - w));
    }
    else
    {
        CR = AQ;
        RB = C.getY() - B.getY();
        if  (RB < 1)
        {
            IR = IB;
            IQ = IB;
        }
        w = CR / RB;
        IR = sum_color(multiply_color(IC, w), multiply_color(IB, 1 - w));
    }
    color_check(IQ);
    color_check(IR);
}

rgb_color convert_to_color(rgb_color IR, rgb_color IQ, int x, int x_from, int x_to)
{
    double t;

    double QP = x - x_from;
    double PR = x_to - x_from;

    if (x == x_from)
    {
        return IQ;
    }
    if (x == x_to)
    {
        return IR;
    }

    t = QP / PR;

    rgb_color IP = sum_color(multiply_color(IQ, t), multiply_color(IR, 1 - t));
    color_check(IP);
    return IP;
}


void ZBuffer :: PutTriangle (Triangle &t) {
    double ymax, ymin, ysc;
    int e1, e;
    Node A, B, C, min_node, middle_node, max_node;
    double x[3], y[3];
    A = t.getNode1();
    B = t.getNode2();
    C = t.getNode3();
    //Заносим x,y из t в массивы для последующей работы с ними
    x[0] = A.getX();
    y[0] = A.getY();
    x[1] = B.getX();
    y[1] = B.getY();
    x[2] = C.getX();
    y[2] = C.getY();
    //Определяем максимальный и минимальный y
    if (y[0] < y[1])
    {
        if (y[0] < y[2])
        {
            ymin = y[0];
            min_node = A;
            if (y[1] < y[2])
            {
                ymax = y[2];
                max_node = C;
                middle_node = B;
            }
            else
            {
                ymax = y[1];
                max_node = B;
                middle_node = C;
            }
        }
        else
        {
            ymin = y[2];
            min_node = C;
            middle_node = A;
            ymax = y[1];
            max_node = B;
        }
    }
    else
    {
        if (y[1] < y[2])
        {
            ymin = y[1];
            min_node = B;
            if (y[0] < y[2])
            {
                ymax = y[2];
                max_node = C;
                middle_node = A;
            }
            else
            {
                ymax = y[0];
                max_node = A;
                middle_node = C;
            }
        }
        else
        {
            ymin = y[2];
            min_node = C;
            middle_node = B;
            ymax = y[0];
            max_node = A;
        }
    }

    ymin = (ymin < 0) ? 0 : ymin;
    ymax = (ymax < sY) ? ymax : sY;
    int ne;
    double x1, x2, xsc1, xsc2, xsc;
    double z1, z2, tc, z;
    int xsc_int, ysc_int, xsc1_int, xsc2_int;
    rgb_color IR, IQ;
    //Следующий участок кода перебирает все строки сцены
    //и определяет глубину каждого пикселя
    //для соответствующего треугольника
    for (ysc = ymin; ysc < ymax; ysc++) {
        ne = 0;
        for (e = 0; e < 3; e++)
        {
            e1 = e + 1;
            if (e1 == 3)
            {
                e1 = 0;
            }
            if (y[e] < y[e1])
            {
                if (y[e1] <= ysc || ysc < y[e])
                {
                    continue;
                }
            }
            else if (y[e] > y[e1])
            {
                if (y[e1] > ysc || ysc >= y[e])
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
            tc = (y[e] - ysc) / (y[e] - y[e1]);
            if (ne)
            {
                x2 = x[e] + tc * (x[e1] - x[e]);
                z2 = t.getNode(e).getZ() + tc * (t.getNode(e1).getZ() - t.getNode(e).getZ());
            }
            else
            {
                x1 = x[e] + tc * (x[e1] - x[e]);
                z1 = t.getNode(e).getZ() + tc * (t.getNode(e1).getZ() - t.getNode(e).getZ());
                ne = 1;
            }
        }
        if (x2 < x1)
        {
            e = x1;
            x1 = x2;
            x2 = e;
            tc = z1;
            z1 = z2;
            z2 = tc;
        }
        xsc1 = (x1 < 0) ? 0 : x1;
        xsc2 = (x2 < sX) ? x2 : sX;
        get_IR_IQ(IR, IQ, min_node, middle_node, max_node, ysc);
        ysc_int = int(ysc);
        xsc1_int = int(xsc1);
        xsc2_int = int(xsc2);
        for (xsc = xsc1; xsc < xsc2; xsc++)
        {
            tc = (x1 - xsc) / (x1 - x2);
            z = z1 + tc * (z2 - z1);
            xsc_int = int(xsc);
            //Если полученная глубина пиксела меньше той,
            //что находится в Z-Буфере - заменяем храняшуюся на новую.
            if (z < buf[ysc_int][xsc_int].z)
            {
                //buf[ysc][xsc].color = {255, 0, 0};
                //buf[ysc][xsc].color = min_node.getcolor();
                buf[ysc_int][xsc_int].color = convert_to_color(IR, IQ, xsc_int, xsc1_int, xsc2_int);
                buf[ysc_int][xsc_int].z = z;
            }
        }
    }
}

/*
void ZBuffer :: PutTriangle (Triangle &t) {
    int ymax, ymin, ysc, e1, e;
    Node A, B, C, min_node, middle_node, max_node;
    int x[3], y[3];
    A = t.getNode1();
    B = t.getNode2();
    C = t.getNode3();
    //Заносим x,y из t в массивы для последующей работы с ними
    x[0] = int(A.getX());
    y[0] = int(A.getY());
    x[1] = int(B.getX());
    y[1] = int(B.getY());
    x[2] = int(C.getX());
    y[2] = int(C.getY());
    //Определяем максимальный и минимальный y
    if (y[0] < y[1])
    {
        if (y[0] < y[2])
        {
            ymin = y[0];
            min_node = A;
            if (y[1] < y[2])
            {
                ymax = y[2];
                max_node = C;
                middle_node = B;
            }
            else
            {
                ymax = y[1];
                max_node = B;
                middle_node = C;
            }
        }
        else
        {
            ymin = y[2];
            min_node = C;
            middle_node = A;
            ymax = y[1];
            max_node = B;
        }
    }
    else
    {
        if (y[1] < y[2])
        {
            ymin = y[1];
            min_node = B;
            if (y[0] < y[2])
            {
                ymax = y[2];
                max_node = C;
                middle_node = A;
            }
            else
            {
                ymax = y[0];
                max_node = A;
                middle_node = C;
            }
        }
        else
        {
            ymin = y[2];
            min_node = C;
            middle_node = B;
            ymax = y[0];
            max_node = A;
        }
    }

    ymin = (ymin < 0) ? 0 : ymin;
    ymax = (ymax < int(sY)) ? ymax : int(sY);
    int ne;
    int x1, x2, xsc1, xsc2, xsc;
    double z1, z2, tc, z;
    rgb_color IR, IQ;
    //Следующий участок кода перебирает все строки сцены
    //и определяет глубину каждого пикселя
    //для соответствующего треугольника
    for (ysc = ymin; ysc < ymax; ysc++) {
        ne = 0;
        for (int e = 0; e < 3; e++)
        {
            e1 = e + 1;
            if (e1 == 3)
            {
                e1 = 0;
            }
            if (y[e] < y[e1])
            {
                if (y[e1] <= ysc || ysc < y[e])
                {
                    continue;
                }
            }
            else if (y[e] > y[e1])
            {
                if (y[e1] > ysc || ysc >= y[e])
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
            tc = double(y[e] - ysc) / (y[e] - y[e1]);
            if (ne)
            {
                x2 = x[e] + int (tc * (x[e1] - x[e]));
                z2 = t.getNode(e).getZ() + tc * (t.getNode(e1).getZ() - t.getNode(e).getZ());
            }
            else
            {
                x1 = x[e] + int(tc * (x[e1] - x[e]));
                z1 = t.getNode(e).getZ() + tc * (t.getNode(e1).getZ() - t.getNode(e).getZ());
                ne = 1;
            }
        }
        if (x2 < x1)
        {
            e = x1;
            x1 = x2;
            x2 = e;
            tc = z1;
            z1 = z2;
            z2 = tc;
        }
        xsc1 = (x1 < 0) ? 0 : x1;
        xsc2 = (x2 < int(sX)) ? x2 : int(sX);
        get_IR_IQ(IR, IQ, min_node, middle_node, max_node, ysc);
        for (xsc = xsc1; xsc < xsc2; xsc++)
        {
            tc = double(x1 - xsc) / (x1 - x2);
            z = z1 + tc * (z2 - z1);
            //Если полученная глубина пиксела меньше той,
            //что находится в Z-Буфере - заменяем храняшуюся на новую.
            if (z < buf[ysc][xsc].z)
            {
                //buf[ysc][xsc].color = {255, 0, 0};
                //buf[ysc][xsc].color = min_node.getcolor();
                buf[ysc][xsc].color = convert_to_color(IR, IQ, xsc, xsc1, xsc2);
                buf[ysc][xsc].z = z;
            }
        }
    }
}*/

#endif // Z_BUFFER_CPP

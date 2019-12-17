#include "drawmanager.h"



Point dif2(Point vec1, Point vec2)
{
    return {vec2.x - vec1.x, vec2.y - vec1.y, vec2.z - vec1.z};
}

Point summ(Point vec1, Point vec2)
{
    return {vec2.x + vec1.x, vec2.y + vec1.y, vec2.z + vec1.z};
}



Point mult_on_number(Point v, double k)
{
    return {v.x * k, v.y * k, v.z * k};
}

Point divide_on_number(Point v, double k)
{
    return {v.x / k, v.y / k, v.z / k};
}


Point get_vect_multy2(Point vec1, Point vec2)
{
    double x = vec1.y * vec2.z - vec1.z * vec2.y;
    double y = - vec1.x * vec2.z + vec1.z * vec2.x;
    double z = vec1.x * vec2.y - vec1.y * vec2.x;
    return {x, y, z};
}


double get_scal_multy(Point vec1, Point vec2)
{

    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

rgb_color get_intensitive_color(rgb_color clr, double intense)
{
    return {int(clr.red * intense),
                int(clr.green * intense),
                int(clr.blue * intense)};
}

double get_length(Point v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Point normalize(Point v)
{
    double d = get_length(v);
    if (d < 0.00001)
    {
        return {0,0,0};
    }
    else
    {
        return {v.x / d, v.y / d, v.z / d};
    }
}



/*
void calc_norms(vector<Triangle> &triangles, Point l_norm)
{
    Point v1, v2, v_norm;
    Node n1, n2, n3;
    double intensity;

    for (size_t i = 0; i < triangles.size(); i++)
    {
        n1 = triangles[i].getNode1();
        n2 = triangles[i].getNode2();
        n3 = triangles[i].getNode3();

        v1 = {n2.getX() - n1.getX(), n2.getY() - n1.getY(), n2.getZ() - n1.getZ()};
        v2 = {n3.getX() - n1.getX(), n3.getY() - n1.getY(), n3.getZ() - n1.getZ()};
        v_norm = get_vect_multy2(v1, v2);
        v_norm = normalize(v_norm);

        intensity = get_scal_multy(v_norm, l_norm);
        triangles[i].setIntensity(intensity);
    }
}

void set_nodes_intensity(vector<Triangle> &triangles, size_t acc)
{
    double sum_up_ints = 0;
    double sum_down_ints = 0;
    double sum_ints;
    double up_ints, down_ints, ints;
    size_t sz = triangles.size();
    for (size_t i = 0; i < sz; i += 2)
    {
        sum_up_ints += triangles[i].getIntensity();
        sum_down_ints += triangles[i + 1].getIntensity();
    }

    up_ints = sum_up_ints / double(sz / 2);
    down_ints = sum_down_ints / double(sz / 2);

    for (size_t i = 0; i < sz; i += 2)
    {
        triangles[i].setNode1Color(get_intensitive_color(triangles[i].getNode1().getcolor(), fabs(up_ints)));
        triangles[i + 1].setNode1Color(get_intensitive_color(triangles[i + 1].getNode1().getcolor(), fabs(down_ints)));
    }

    double before_up_ints, before_down_ints;

    size_t acc_2 = acc * 2;

    for (size_t j = 0; j < sz; j += acc_2)
    {
        before_up_ints = triangles[j + acc - 2].getIntensity();
        before_down_ints = triangles[j + acc - 1].getIntensity();
        for (size_t i = 0; i < acc; i += 2)
        {
            up_ints = triangles[j + i].getIntensity();
            down_ints = triangles[j + i + 1].getIntensity();
            sum_ints = up_ints + down_ints + before_up_ints + before_down_ints;
            before_up_ints = up_ints;
            before_down_ints = down_ints;

            ints = sum_ints / 4;

            triangles[j + i].setNode2Color(get_intensitive_color(triangles[j + i].getNode2().getcolor(), fabs(ints)));
            triangles[j + i + 1].setNode2Color(get_intensitive_color(triangles[j + i + 1].getNode2().getcolor(), fabs(ints)));
        }

        triangles[j + acc - 2].setNode3Color(triangles[j + 0].getNode2().getcolor());
        triangles[j + acc - 1].setNode3Color(triangles[j + 1].getNode2().getcolor());
        for (size_t i = 0; i < acc - 2; i += 2)
        {
            triangles[j + i].setNode3Color(triangles[j + i + 2].getNode2().getcolor());
            triangles[j + i + 1].setNode3Color(triangles[j + i + 3].getNode2().getcolor());
        }
    }
}*/


void calc_norms(vector<Triangle> &triangles)
{
    Point v1, v2, v_norm;
    Node n1, n2, n3;

    for (size_t i = 0; i < triangles.size(); i++)
    {
        n1 = triangles[i].getNode1();
        n2 = triangles[i].getNode2();
        n3 = triangles[i].getNode3();

        v1 = {n2.getX() - n1.getX(), n2.getY() - n1.getY(), n2.getZ() - n1.getZ()};
        v2 = {n3.getX() - n1.getX(), n3.getY() - n1.getY(), n3.getZ() - n1.getZ()};
        v_norm = get_vect_multy2(v1, v2);
        v_norm = normalize(v_norm);

        triangles[i].setNorm(v_norm);
    }
}

void set_nodes_intensity(vector<Triangle> &triangles, size_t acc, Point l_norm, double l_intense)
{
    Point sum_up_ints = {0, 0, 0};
    Point sum_down_ints = {0, 0, 0};
    Point sum_ints = {0, 0, 0};
    Point up_ints, down_ints, ints;
    size_t sz = triangles.size();
    double intensity_up, intensity_down;

    for (size_t i = 0; i < sz; i += 2)
    {
        sum_up_ints = summ(sum_up_ints, triangles[i].getNorm());
        sum_down_ints = summ(sum_down_ints, triangles[i + 1].getNorm());
    }

    up_ints = divide_on_number(sum_up_ints, double(sz / 2));
    down_ints = divide_on_number(sum_down_ints, double(sz / 2));

    intensity_up = get_scal_multy(up_ints, l_norm);
    intensity_down = get_scal_multy(down_ints, l_norm);

    for (size_t i = 0; i < sz; i += 2)
    {
        triangles[i].setNode1Color(get_intensitive_color(triangles[i].getNode1().getcolor(), intensity_up * l_intense));
        triangles[i + 1].setNode1Color(get_intensitive_color(triangles[i + 1].getNode1().getcolor(), intensity_down * l_intense));
    }

    Point before_up_ints, before_down_ints;

    double intensity;

    size_t acc_2 = acc * 2;

    for (size_t j = 0; j < sz; j += acc_2)
    {
        before_up_ints = triangles[j + acc_2 - 2].getNorm();
        before_down_ints = triangles[j + acc_2 - 1].getNorm();
        for (size_t i = 0; i < acc_2; i += 2)
        {
            up_ints = triangles[j + i].getNorm();
            down_ints = triangles[j + i + 1].getNorm();
            sum_ints = summ(summ(summ(up_ints,down_ints), before_up_ints), before_down_ints);
            before_up_ints = up_ints;
            before_down_ints = down_ints;

            ints = divide_on_number(sum_ints, 4);


            intensity = get_scal_multy(ints, l_norm);

            triangles[j + i].setNode2Color(get_intensitive_color(triangles[j + i].getNode2().getcolor(), intensity * l_intense));
            triangles[j + i + 1].setNode2Color(get_intensitive_color(triangles[j + i + 1].getNode2().getcolor(), intensity * l_intense));
        }

        triangles[j + acc_2 - 2].setNode3Color(triangles[j + 0].getNode2().getcolor());
        triangles[j + acc_2 - 1].setNode3Color(triangles[j + 1].getNode2().getcolor());
        for (size_t i = 0; i < acc_2 - 2; i += 2)
        {
            triangles[j + i].setNode3Color(triangles[j + i + 2].getNode2().getcolor());
            triangles[j + i + 1].setNode3Color(triangles[j + i + 3].getNode2().getcolor());
        }
    }
}



void get_axes_coords(vector<Point> &coords)
{
    //x
    coords.push_back({-349, 0, 0});
    coords.push_back({349, 0, 0});
    //y
    coords.push_back({0, -349, 0});
    coords.push_back({0, 349, 0});
    //z
    coords.push_back({0, 0, -349});
    coords.push_back({0, 0, 349});
}

void transform_coord(shared_ptr<Camera> cm, Point &p)
{
    p.shift(cm->getShX(), cm->getShY(), cm->getShZ());
    p.scale(cm->getScX(), cm->getScY(), cm->getScZ());

    p.rotate(cm->getRtX(), cm->getRtY(), cm->getRtZ());

    p.shift(350, 350, 0);
}


void DrawManager::print_coords_axes(shared_ptr<Camera> cm, vector<Point> &coords)
{
    get_axes_coords(coords);
    for (size_t i = 0; i < coords.size(); i += 2)
    {
        transform_coord(cm, coords[i]);
        transform_coord(cm, coords[i + 1]);
    }
}


void DrawManager::drawcolorfulModel(BaseDrawer& drw, const ObjIter& b, const ObjIter& e, \
               shared_ptr<Object> obj)
{
    shared_ptr<Camera> cm = std::static_pointer_cast<Camera>(obj);
    for (ObjIter iter = b; iter != e; ++iter)
    {
        if (!(*iter))
            throw NoDrawingObjectException();

        if ((*iter)->isVisible())
        {
            shared_ptr<Transformed_Model> model = std::static_pointer_cast<Transformed_Model>(*iter);

            vector<Triangle> triangles = model->getTriangles();
            if (triangles.empty())
                throw NoDrawingTrianglesException();



            size_t acc = model->getAccuracy();




            //transform_coord(cm, l_from);
            //transform_coord(cm, l_to);

            Point l_norm = drw.getLighting();

            double l_intensity = drw.getIntensity();

            //Point l_from = {0,0,-99999};
            //Point l_to = {0,0,99999};
            //lighting l = {l_from, l_to};
            //Point l_norm = normalize(dif2(l.from, l.to));

            //calc_norms(triangles, l_norm);
            //set_nodes_intensity(triangles, acc);

            calc_norms(triangles);
            set_nodes_intensity(triangles, acc, l_norm, l_intensity);



            //перемещение, вращение и масштабирование точек
            for (size_t i = 0; i < triangles.size(); ++i)
            {
                triangles[i].shift(cm->getShX(), cm->getShY(), cm->getShZ());
                triangles[i].scale(cm->getScX(), cm->getScY(), cm->getScZ());

                triangles[i].rotateX(cm->getRtX());
                triangles[i].rotateY(cm->getRtY());
                triangles[i].rotateZ(cm->getRtZ());

                triangles[i].shift(350, 350, 0);
            }





            ZBuffer buf(700, 700);
            buf.Clear();


            //Плоская закраска
            /*Triangle triangle;

            Node n1, n2, n3;

            Point v1, v2, v_norm;

            rgb_color clr = triangles[0].getNode1().getcolor();

            for (size_t i = 0; i < triangles.size(); i++)
            {
                triangle = triangles[i];
                n1 = triangle.getNode1();
                n2 = triangle.getNode2();
                n3 = triangle.getNode3();
                v1 = {n2.getX() - n1.getX(), n2.getY() - n1.getY(), n2.getZ() - n1.getZ()};
                v2 = {n3.getX() - n1.getX(), n3.getY() - n1.getY(), n3.getZ() - n1.getZ()};
                v_norm = get_vect_multy2(v1, v2);
                v_norm = normalize(v_norm);

                double intensity = get_scal_multy(v_norm, l_norm);
                triangle.setNode1Color(get_intensitive_color(clr, fabs(intensity)));
                triangle.setNode2Color(get_intensitive_color(clr, fabs(intensity)));
                triangle.setNode3Color(get_intensitive_color(clr, fabs(intensity)));
                buf.PutTriangle(triangle);
            }
            buf.Show(drw);*/



            //Закраска Гуро




            /*for (size_t i = 0; i < acc * 2; i++)
            {
                buf.PutTriangle(triangles[i]);
            }*/



            for (size_t i = 0; i < triangles.size(); i++)
            {
                buf.PutTriangle(triangles[i]);
            }


            vector<Point> coords;
            print_coords_axes(cm, coords);

            rgb_color red = {255, 0, 0};
            rgb_color green = {0, 255, 0};
            rgb_color blue = {0, 0, 255};

            buf.PutAxes(coords[0], coords[1], red);
            buf.PutAxes(coords[1], coords[0], red);

            buf.PutAxes(coords[2], coords[3], green);
            buf.PutAxes(coords[3], coords[2], green);

            buf.PutAxes(coords[4], coords[5], blue);
            buf.PutAxes(coords[5], coords[4], blue);

            buf.Show(drw);









            /*for (size_t i = 0; i < nodes.size(); ++i)
            {
                drw.addPoint(getX(nodes[i].getX(), nodes[i].getZ()),
                             getY(nodes[i].getY(), nodes[i].getZ()),
                             nodes[i].getcolor());
            }
            drw.draw();*/

            /*Node node1, node2, node3;
            for (size_t i = 0; i < triangles.size(); i++)
            {
                node1 = triangles[i].getNode1();
                node2 = triangles[i].getNode2();
                node3 = triangles[i].getNode3();
                drw.addLine(getX(node1.getX(), node1.getZ()),
                            getY(node1.getY(), node1.getZ()), getX(node2.getX(), node2.getZ()),
                            getY(node2.getY(), node2.getZ()), triangles[i].getColor());
                drw.addLine(getX(node1.getX(), node1.getZ()),
                            getY(node1.getY(), node1.getZ()), getX(node3.getX(), node3.getZ()),
                            getY(node3.getY(), node3.getZ()), triangles[i].getColor());
                drw.addLine(getX(node2.getX(), node2.getZ()),
                            getY(node2.getY(), node2.getZ()), getX(node3.getX(), node3.getZ()),
                            getY(node3.getY(), node3.getZ()), triangles[i].getColor());
            }*/
            /*for (size_t i = 0; i < nodes.size(); ++i)
            {
                drw.addPoint(getX(nodes[i].getX(), nodes[i].getZ()),
                             getY(nodes[i].getY(), nodes[i].getZ()),
                             nodes[i].getcolor());
                drw.addLine()
            }*/
            //drw.draw();
        }
    }
}


void DrawManager::drawModel(BaseDrawer& drw, const ObjIter& b, const ObjIter& e, \
               std::shared_ptr<Object> obj)
{
    /*std::shared_ptr<Camera> cm = std::static_pointer_cast<Camera>(obj);
    for (ObjIter iter = b; iter != e; ++iter)
    {
        if (!(*iter))
            throw NoDrawingObjectException();

        if ((*iter)->isVisible())
        {
            std::shared_ptr<Model> model = std::static_pointer_cast<Model>(*iter);


            std::vector<Node> nodes = model->getNodes();
            if (nodes.empty())
                throw NoDrawingNodesException();

            for (size_t i = 0; i < nodes.size(); ++i)
            {
                nodes[i].shift(cm->getShX(), cm->getShY(), cm->getShZ());
                nodes[i].scale(cm->getScX(), cm->getScY(), cm->getScZ());

                nodes[i].rotateX(cm->getRtX());
                nodes[i].rotateY(cm->getRtY());
                nodes[i].rotateZ(cm->getRtZ());
            }

            for (size_t i = 0; i < nodes.size(); ++i)
            {
                drw.addPoint(getX(nodes[i].getX(), nodes[i].getZ()),
                             getY(nodes[i].getY(), nodes[i].getZ()),
                             nodes[i].getcolor());
            }
            drw.draw();

        }
    }*/
}

int DrawManager::getX(const double x, const double z) const
{
    return int(x + z * coeff3D);
}

int DrawManager::getY(const double y, const double z) const
{
    return int(-y - z * coeff3D);
}

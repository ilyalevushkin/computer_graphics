#ifndef OBJECT_FACTORY_HPP
#define OBJECT_FACTORY_HPP

#include "object_factory.h"


using namespace std;

std::shared_ptr<Transform_Tree> Transform_Tree::create_Transform_Tree(Transform_Tree_ID id)
{
    std::shared_ptr<Transform_Tree> ptr(nullptr);
    switch (id)
    {
        case Cone_ID:
            ptr = std::make_shared<Cone>();
            break;
    }
    return ptr;
};

double get_d(double y, double z)
{
    return sqrt(y * y + z * z);
}


int srznach(int a, int b)
{
    return (a + b) / 2;
}

rgb_color get_new_color(rgb_color clr1, rgb_color clr2)
{
    return {srznach(clr1.red,clr2.red),
            srznach(clr1.green,clr2.green),
            srznach(clr1.blue,clr2.blue)};
}

void fill_transformed_model(std::shared_ptr<Transformed_Model> model, std::vector<Triangle> cone, size_t acc)
{
    for (size_t i = 0; i < cone.size(); i++)
    {
        model->addTriangle(cone[i]);
    }
    model->addAccuracy(acc);
}

bool get_transform_matrix(Node node1, Node node2, mat &transform)
{
    //задаем начальные параметры для матрицы преобразований
    vec vec1 = {node1.getX(), node1.getY(), node1.getZ()};
    vec vec2 = {node2.getX(), node2.getY(), node2.getZ()};
    vec dif = vec2 - vec1;
    vec norm_vec = normalise(dif);
    double d = get_d(norm_vec[1], norm_vec[2]);
    if (fabs(d) < 0.00001)
    {
        return false;
    }
    double cos_alpha = norm_vec[2] / d;
    double sin_alpha = norm_vec[1] / d;
    double cos_betta = d;
    double sin_betta = norm_vec[0];
    //формируем матрицу преобразований
    transform = matrix::get_turn_matrix(-vec1[0], -vec1[1], -vec1[2]) *
            matrix::get_rotate_round_ox_matrix(cos_alpha, sin_alpha) *
            matrix::get_rotate_round_oy_matrix(cos_betta, -sin_betta);
    return true;
}


double get_angle(int acc)
{
    return 2 * M_PI / double(acc);
}

void get_triangle_coord(double &x, double &y, double angle, double r)
{
    x = r * cos(angle);
    y = r * sin(angle);
}

void fill_mat_row(mat &tree, int i, double x, double y, double z)
{
    tree(i,0) = x;
    tree(i,1) = y;
    tree(i,2) = z;
    tree(i,3) = 1;
}

mat get_mat_cone(mat section, int acc, double radius)
{
    //acc - количество треугольников
    mat result(acc + 2, 4);
    double angle = get_angle(acc);
    double x1, y1;
    int k;
    Point cone_peak = {section(1,0), section(1,1), section(1,2)};
    Point cone_down = {section(0,0), section(0,1), section(0,2)};
    fill_mat_row(result, 0, cone_peak.x, cone_peak.y, cone_peak.z);
    fill_mat_row(result, 1, cone_down.x, cone_down.y, cone_down.z);
    for (int i = 1; i <= acc; i++)
    {
        get_triangle_coord(x1, y1, angle * i, radius);
        fill_mat_row(result, i + 1, x1, y1, 0);
    }
    return result;
}


Node get_node_from_mat(mat m, size_t i, rgb_color rgb)
{
    Node n(m(i, 0), m(i, 1), m(i, 2), rgb);
    return n;
}


void convert_mat_to_triangle(mat m, std::vector<Triangle> &cone, rgb_color clr)
{
    size_t n = size_t(size(m).n_rows);
    Node n_up = get_node_from_mat(m, 0, clr);
    Node n_down = get_node_from_mat(m, 1, clr);
    Node n1;
    Node n2;
    Node n_after;
    for (size_t i = 0; i < n - 2; i++)
    {
        if (i != n - 3)
        {
            if (i == 0)
            {
                n1 = get_node_from_mat(m, 2, clr);
                n2 = get_node_from_mat(m, 3, clr);
                n_after = n1;
            }
            else
            {
                n1 = n2;
                n2 = get_node_from_mat(m, i + 3, clr);
            }
        }
        else
        {
            n1 = n2;
            n2 = n_after;
        }
        Triangle triangle1(n_up, n1, n2);
        Triangle triangle2(n_down, n1, n2);
        cone.push_back(triangle1);
        cone.push_back(triangle2);
    }
}

bool calc_triangles(Node node1, Node node2, rgb_color clr, std::vector<Triangle> &cone, int accuracy, double radius)
{
    //формируем матрицу из 2 точек отрезка (начало конец).
    mat section = {{node1.getX(), node1.getY(), node1.getZ(), 1},
                   {node2.getX(), node2.getY(), node2.getZ(), 1}};
    mat transform;
    if (!get_transform_matrix(node1, node2, transform))
    {
        return false;
    }
    mat transformed_section = section * transform;
    mat mat_cone = get_mat_cone(transformed_section, accuracy, radius);
    convert_mat_to_triangle(mat_cone * transform.i(), cone, clr);
    return true;
}

std::shared_ptr<Transformed_Model> Cone::buildModel(std::shared_ptr<Model> model)
{
    vector<Node> nodes = model->getNodes();
    vector<Edge> edges = model->getEdges();

    Node node1, node2;
    double radius;
    rgb_color new_color;

    //задаем точность разбиения конуса на треугольники (должна быть четной)
    size_t accuracy = 30;

    //проходимся по всем ребрам
    for (size_t i = 0; i < edges.size(); i++)
    {
        std::vector<Triangle> cone;

        node1 = nodes[edges[i].getSrc()];
        node2 = nodes[edges[i].getPurp()];
        radius = edges[i].getRadius();

        //высчитываем новый цвет цилиндра
        new_color = get_new_color(node1.getcolor(), node2.getcolor());

        //хочу сделать ствол красненьким
        new_color = {255, 30, 40};

        //высчитываем новую матрицу точек
        if (calc_triangles(node1, node2, new_color, cone, accuracy, radius))
        {
            //добавляем результат в нашу модель
            fill_transformed_model(transformed_model, cone, accuracy);
        }
    }


    return transformed_model;
}

/*
double get_d(double y, double z)
{
    return sqrt(y * y + z * z);
}


void put_in_result(mat &m, double x, double y, double z, int counter)
{
    m(counter - 4, 0) = x;
    m(counter - 4, 1) = y;
    m(counter - 4, 2) = z;
    m(counter - 4, 3) = z;

    m(counter - 3, 0) = x;
    m(counter - 3, 1) = -y;
    m(counter - 3, 2) = z;
    m(counter - 4, 3) = z;

    m(counter - 2, 0) = -x;
    m(counter - 2, 1) = y;
    m(counter - 2, 2) = z;
    m(counter - 4, 3) = z;

    m(counter - 1, 0) = -x;
    m(counter - 1, 1) = -y;
    m(counter - 1, 2) = z;
    m(counter - 4, 3) = z;
}

mat get_brezenhem_circle(const double R, double z)
{
    double x = 0;
    double y = R;
    double delta = 1 - 2 * R;
    double error = 0;
    int counter = 0;
    while (y >= 0)
    {
        counter += 4;
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0))
        {
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0))
        {
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - y--);
    }

    mat result(counter, 4);
    x = 0;
    y = R;
    delta = 1 - 2 * R;
    error = 0;
    counter = 0;
    while (y >= 0)
    {
        counter += 4;
        put_in_result(result, x, y, z, counter);
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0))
        {
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0))
        {
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - y--);
    }
    return result;
}


void copy_circle_to_obj(mat &obj, mat &circle, double z, int i)
{
    int circle_sz = size(circle).n_rows;
    int circle_sz_i = circle_sz * i;
    for (int j = 0; j < circle_sz; j++)
    {
        obj(circle_sz_i + j,0) = circle(j,0);
        obj(circle_sz_i + j,1) = circle(j,1);
        obj(circle_sz_i + j,2) = z;
        obj(circle_sz_i + j,3) = 1;
    }
}

mat transfer_to_cylinder(mat dots)
{
    const double radius = 10;
    double z1 = dots(0,2);
    double z2 = dots(1,2);
    mat circle = get_brezenhem_circle(radius, z1);
    mat obj(size(circle).n_rows * abs(floor(z2 - z1 + 1)), 4);
    int i = 0;
    while (z1 < z2)
    {
        copy_circle_to_obj(obj, circle, z1, i);
        z1 += 1;
        i++;
    }
    return obj;
}


int srznach(int a, int b)
{
    return (a + b) / 2;
}

rgb_color get_new_color(rgb_color clr1, rgb_color clr2)
{
    return {srznach(clr1.red,clr2.red),
            srznach(clr1.green,clr2.green),
            srznach(clr1.blue,clr2.blue)};
}


void fill_transformed_model(std::shared_ptr<Transformed_Model> model, mat res, rgb_color clr)
{
    Node node;
    for (int i = 0; i < int(size(res).n_rows); i++)
    {
        node = {res(i,0), res(i,1), res(i,2), clr};
        model->addNode(node);
    }
}


bool calc_new_matr(Node node1, Node node2, mat section, mat &res)
{
    //задаем начальные параметры для матрицы преобразований
    vec vec1 = {node1.getX(), node1.getY(), node1.getZ()};
    vec vec2 = {node2.getX(), node2.getY(), node2.getZ()};
    vec dif = vec2 - vec1;
    vec norm_vec = normalise(dif);
    double d = get_d(norm_vec[1], norm_vec[2]);
    if (fabs(d) < 0.00001)
    {
        return false;
    }
    double cos_alpha = norm_vec[2] / d;
    double sin_alpha = norm_vec[1] / d;
    double cos_betta = d;
    double sin_betta = norm_vec[0];
    //формируем матрицу преобразований
    mat transform = matrix::get_turn_matrix(-vec1[0], -vec1[1], -vec1[2]) *
            matrix::get_rotate_round_ox_matrix(cos_alpha, sin_alpha) *
            matrix::get_rotate_round_oy_matrix(cos_betta, -sin_betta);
    //проводим преобразования
    res = transfer_to_cylinder(section * transform) * transform.i();
    return true;
}

std::shared_ptr<Transformed_Model> Cylinder::buildModel(std::shared_ptr<Model> model)
{
    vector<Node> nodes = model->getNodes();
    vector<Edge> edges = model->getEdges();
    //Здесь будет отрезок преобразовываться в цилиндр в виде точек, а пока просто 2 точки

    Node node1, node2, norm_vec;
    mat section;
    mat res;
    //проходимся по всем ребрам
    for (size_t i = 0; i < edges.size(); i++)
    {
        node1 = nodes[edges[i].getSrc()];
        node2 = nodes[edges[i].getPurp()];

        //формируем матрицу из 2 точек отрезка (начало конец).
        section = {{node1.getX(), node1.getY(), node1.getZ(), 1},
                  {node2.getX(), node2.getY(), node2.getZ(), 1}};

        //высчитываем новую матрицу точек
        if (calc_new_matr(node1, node2, section, res))
        {
            //высчитываем новый цвет цилиндра
            rgb_color new_color = get_new_color(node1.getcolor(), node2.getcolor());
            //добавляем результат в нашу модель
            fill_transformed_model(transformed_model, res, new_color);
        }
    }


    return transformed_model;
}*/



#endif // OBJECT_FACTORY_HPP

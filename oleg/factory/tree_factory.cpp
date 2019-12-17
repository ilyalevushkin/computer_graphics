#ifndef TREE_FACTORY_CPP
#define TREE_FACTORY_CPP

#include "tree_factory.h"

using namespace std;

std::shared_ptr<Tree> Tree::createTree(Tree_ID id)
{
    std::shared_ptr<Tree> ptr(nullptr);
    switch (id)
    {
        case Honda_ID:
            ptr = std::make_shared<Honda>();
            break;
    }
    return ptr;
};

struct Branch
{
    int depth;
    Point point1;
    Point point2;
    double radius;
};

struct Branch_param
{
    double koef_start;
    double koef_length;
    double angle;
};

struct Binary_Tree
{
    Branch br;
    Binary_Tree *left;
    Binary_Tree *right;
};


double calc_length(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z));
}

double create_radius(Branch br, double k)
{
    double length = calc_length(br.point1, br.point2);
    double BE = length - length / k;
    double new_k = length / BE;
    return br.radius / new_k;
}

size_t get_tree_branches(size_t deep_tree)
{
    return size_t(pow(2, deep_tree + 1) - 1);
}


void fill_mat_row(mat &tree, int i, Point p)
{
    tree(i,0) = p.x;
    tree(i,1) = p.y;
    tree(i,2) = p.z;
    tree(i,3) = 1;
}


void edges_fill(std::shared_ptr<Model> model, size_t amount, vector<double> radius)
{
    for (size_t i = 0; i < amount / 2; i++)
    {
        Edge edge(i * 2, i * 2 + 1, radius[i]);
        model->addEdge(edge);
    }
}


Branch create_root(double length, double radius)
{
    Branch root;
    root.point1 = {0,0,0};
    root.point2 = {0,0,length};
    root.radius = radius;
    return root;
}

void create_main_branches(Binary_Tree *left, Binary_Tree *right, tree_params params, Branch root)
{
    double l_start, r_start, l_length, r_length;
    l_start = params.body_length.length / params.koef.l_start;
    r_start = params.body_length.length / params.koef.r_start;
    l_length = params.body_length.length / params.koef.l_length;
    r_length = params.body_length.length / params.koef.r_length;

    double x_left = sin(params.angles.alpha1) * l_length;
    double y_left = 0;
    double z_left = l_start + cos(params.angles.alpha1) * l_length;

    double r_length_projection = sin(params.angles.alpha2) * r_length;
    double x_right = cos(params.angles.alpha) * r_length_projection;
    double y_right = sin(params.angles.alpha) * r_length_projection;
    double z_right = r_start + cos(params.angles.alpha2) * r_length;

    double radius;

    radius = create_radius(root, params.koef.l_start);
    left->br = {1, {0, 0, l_start}, {x_left, y_left, z_left}, radius};
    left->left = nullptr;
    left->right = nullptr;

    radius = create_radius(root, params.koef.r_start);
    right->br = {1, {0, 0, r_start}, {x_right, y_right, z_right}, radius};
    right->left = nullptr;
    right->right = nullptr;
}


void add_branch(mat &tree, int &i, Branch br)
{
    fill_mat_row(tree, i, br.point1);
    fill_mat_row(tree, i + 1, br.point2);
    i += 2;
}
/*
bool check_coord(double coord)
{
    double max_double = numeric_limits<double>::max();
    return fabs(coord) < MIN_VALUE;
}

bool check_Point(Point p)
{
    return check_coord(p.x) && check_coord(p.y) && check_coord(p.z);
}

bool check_br(Branch br)
{
    return check_Point(br.point1) && check_Point(br.point2);
}*/

double calc_new_length(double k, double length)
{
    return (fabs(length) < MIN_VALUE) ? 0 : length / k;
}

double get_first_coord(double k, double x1, double x2)
{
    return (x2 - x1) / k + x1;
}

Point get_first_point(double k, Branch br)
{
    return {get_first_coord(k, br.point1.x, br.point2.x),
                get_first_coord(k, br.point1.y, br.point2.y),
                get_first_coord(k, br.point1.z, br.point2.z)};
}

Point get_perpendicular_point(double l, Point A, Point B, Point C, bool flag)
{
    double c = B.x - A.x;
    double d = B.y - A.y;
    double denominator = sqrt(pow(d,2) + pow(c,2));
    double b = l * c / denominator;
    double a = -l * d / denominator;
    if (flag)
    {
        b *= -1;
        a *= -1;
    }
    return {C.x + a, C.y + b, C.z};
}


Point dif(Point A, Point B)
{
    return {B.x - A.x, B.y - A.y, B.z - A.z};
}

Point get_vect_multy(Point vec1, Point vec2)
{
    double x = vec1.y * vec2.z - vec1.z * vec2.y;
    double y = - vec1.x * vec2.z + vec1.z * vec2.x;
    double z = vec1.x * vec2.y - vec1.y * vec2.x;
    return {x, y, z};
}

bool norm_vector(Point &vec)
{
    double norm = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    if (fabs(norm) < 0.000001)
    {
        return false;
    }
    else
    {
        double x = vec.x / norm;
        double y = vec.y / norm;
        double z = vec.z / norm;
        vec = {x,y,z};
        return true;
    }
}

bool check_right_orientation(Point vec1, Point vec2, Point vec3)
{
    mat m = {
        {vec1.x, vec1.y, vec1.z},
        {vec2.x, vec2.y, vec2.z},
        {vec3.x, vec3.y, vec3.z}
    };
    double d = det(m);
    return d > 0;
}

Point get_rotate_point(Point A, Point B, Point C, Point D, double angle)
{
    //создаем направляющий вектор
    Point direct_vector = get_vect_multy(dif(A,B), dif(C,D));

    /*if (!check_right_orientation(dif(A,B), dif(C,D), direct_vector))
    {
        //angle *= -1;
        direct_vector.x *= -1;
        direct_vector.y *= -1;
        direct_vector.z *= -1;
    }*/

    //нормируем его
    if (!norm_vector(direct_vector))
    {
        return D;
    }

    //создаем матрицу из одной точки, которую необходимо повернуть вокруг направляющего вектора
    mat rotate_dot(1,4);
    rotate_dot = {D.x, D.y, D.z, 1};
    //объявляем матрицу смещения в начало координат
    mat shift = matrix::get_turn_matrix(-C.x, -C.y, -C.z);
    double d = sqrt(direct_vector.y * direct_vector.y + direct_vector.z * direct_vector.z);
    //объявляем матрицу поворота вокруг оси ox
    mat ox_rotate = matrix::get_rotate_round_ox_matrix(direct_vector.z / d, direct_vector.y / d);
    //объявляем матрицу поворота вокруг оси oy
    mat oy_rotate = matrix::get_rotate_round_oy_matrix(d, -direct_vector.x);
    //объявляем матрицу поворота на угол angle
    mat angle_rotate = matrix::get_rotate_round_oz_matrix(cos(angle), sin(angle));
    //создаем матрицу преобразований
    mat transform = shift * ox_rotate * oy_rotate;
    //преобразуем
    rotate_dot = rotate_dot * transform * angle_rotate * transform.i();
    //получаем конечную точку
    return {rotate_dot(0,0), rotate_dot(0,1), rotate_dot(0,2)};
}

Branch create_next_branch(Binary_Tree last_br, Branch_param params, bool flag, int depth)
{
    //Обьявляем точки A и B (концы старой ветки)
    Point A = {last_br.br.point1.x, last_br.br.point1.y, last_br.br.point1.z};
    Point B = {last_br.br.point2.x, last_br.br.point2.y, last_br.br.point2.z};
    //высчитываем длину старой ветки
    double last_length = sqrt(pow(A.x - B.x,2) +
                              pow(A.y - B.y,2) +
                              pow(A.z - B.z,2));
    //высчитываем длину новой ветки
    double length = calc_new_length(params.koef_length, last_length);
    //вычисляем первую точку новой ветки (точка C)
    Point C = get_first_point(params.koef_start, last_br.br);

    //вычисляем точку D (отрезок CD перпендикулярен отрезку AB и CD параллельна Oxy)
    Point D = get_perpendicular_point(length, A, B, C, flag);

    //поворачиваем точку D на нужный угол
    if (check_right_orientation(get_vect_multy(dif(A,B), dif(C,D)), dif(A,B), dif(C, D)))
    {
        //params.angle = M_PI / 2 - params.angle;
        params.angle -= M_PI / 2;
    }
    /*else
    {
        params.angle = M_PI / 2 - params.angle;
    }*/
    Point Rotate_D = get_rotate_point(A, B, C, D, params.angle);

    double radius = create_radius(last_br.br, params.koef_start);

    return {depth, C, Rotate_D, radius};
}

void create_branches(Binary_Tree *brs, Branch_param l_par, Branch_param r_par, size_t k, size_t deep)
{
    if (k != deep)
    {
        Binary_Tree *left = new Binary_Tree();
        Binary_Tree *right = new Binary_Tree();
        //l_par.angle -= M_PI / 2;
        //r_par.angle -= M_PI / 2;
        //r_par.angle = -r_par.angle - M_PI / 2;
        //r_par.angle = M_PI - r_par.angle;
        //r_par.angle = -r_par.angle + M_PI / 2;
        k++;
        left->br = create_next_branch(*brs, l_par, true, int(k));
        right->br = create_next_branch(*brs, r_par, false, int(k));
        brs->left = left;
        brs->right = right;
        create_branches(left, l_par, r_par, k, deep);
        create_branches(right, l_par, r_par, k, deep);
    }
    else
    {
        brs->left = nullptr;
        brs->right = nullptr;
    }
}

void clear_branches(Binary_Tree *tree)
{
    if (tree != nullptr)
    {
        Binary_Tree *left = tree->left;
        Binary_Tree *right = tree->right;
        if (left != nullptr)
        {
            clear_branches(left);
        }
        if (right != nullptr)
        {
            clear_branches(right);
        }
        delete tree;
    }
}


void add_branches(mat &tree, int &i, Binary_Tree *brs, vector<int> &brs_deep, vector<double> &radius)
{
    //обход дерева

    if (brs != nullptr)
    {
        brs_deep[int(i / 2)] = brs->br.depth;
        add_branch(tree, i, brs->br);
        radius.push_back(brs->br.radius);
        if (brs->left != nullptr)
        {
            add_branches(tree, i, brs->left, brs_deep, radius);
        }
        if (brs->right != nullptr)
        {
            add_branches(tree, i, brs->right, brs_deep, radius);
        }
    }
}


void tree_generate(mat &tree, tree_params params, size_t branches, size_t deep, vector<int> &brs_deep, vector<double> &radius)
{
    int i = 0;
    double rad = 15;
    Branch root = create_root(params.body_length.length, rad);
    add_branch(tree, i, root);
    radius.push_back(rad);
    //задаем количество веток дерева
    Binary_Tree *left_branches = new Binary_Tree();
    Binary_Tree *right_branches = new Binary_Tree();
    create_main_branches(left_branches, right_branches, params, root);

    Branch_param left_params = {params.koef.l_start, params.koef.l_length, params.angles.alpha1};
    Branch_param right_params = {params.koef.r_start, params.koef.r_length, params.angles.alpha2};

    create_branches(left_branches, left_params, right_params, 1, deep);
    create_branches(right_branches, left_params, right_params, 1, deep);

    brs_deep[0] = 0;
    add_branches(tree, i, left_branches, brs_deep, radius);
    add_branches(tree, i, right_branches, brs_deep, radius);

    clear_branches(left_branches);
    clear_branches(right_branches);
}

void nodes_fill(std::shared_ptr<Model> model, mat tree)
{
    for (size_t i = 0; i < size(tree).n_rows; i++)
    {
        int r = i % 256;
        int g = i * 2 % 256;
        int b = i * 3 % 256;
        rgb_color clr = {r,g,b};
        Node node(tree(i,0), tree(i,1), tree(i,2), clr);
        model->addNode(node);
    }
}


void move_nodes(mat &tree)
{
    for (size_t i = 0; i < size(tree).n_rows; i++)
    {
        tree(i,0) += 350;
        tree(i,1) -= 350;
    }
}

vector<double> create_branches_radius(size_t n, vector<int> depth, int max_depth)
{
    vector<double> mas(n);
    int k;

    //size_t branches = size_t((n - 1) / 2);

    for (size_t i = 1; i < (n - 1 / 2); i++)
    {
        mas[i] = max_depth - depth[i] + 1;
    }
    mas[0] = 10;
    return mas;
}

std::shared_ptr<Transformed_Model> Honda::buildModel(tree_params params, std::shared_ptr<Transform_Tree> tr_tree)
{
    /*for (int i = 0; i < 100; i++)
    {
        Node node(params.dot.x, params.dot.y, params.dot.z + i, {i,2*i,255});
        this->model->addNode(node);
    }*/
    /*Node node1(params.dot.x, params.dot.y, params.dot.z, {0,0,255});
    Node node2(params.dot.x, params.dot.y, params.dot.z + 100,{0,0,255});
    this->model->addNode(node1);
    this->model->addNode(node2);
    Edge edge(0, 1);
    this->model->addEdge(edge);*/
    //Здесь будет строиться дерево методом Хонда, а пока просто палка

    vector<double> branch_radius;

    //задаем глубину дерева (отсчет идет начиная с 1 ветки (ствол не считается))
    size_t deep_tree = 5;
    //создаем матрицу преобразований
    size_t branches = get_tree_branches(deep_tree);
    vector<int> depth(branches);
    size_t nodes_amount = branches * 2;
    mat tree(nodes_amount, 4);
    //создаем матрицу переноса
    mat turn_matrix = matrix::get_turn_matrix(params.dot.x,params.dot.y, params.dot.z);
    //генерируем дерево
    tree_generate(tree, params, branches, deep_tree, depth, branch_radius);
    //возвращаем дерево на сходную позицию
    tree = tree * turn_matrix;

    //создаем массив радиусов оснований каждой ветки
    //vector<double> branch_radius = create_branches_radius(branches, depth, deep_tree);

    //соединяем каждый отрезок линией (заполняем edges)
    edges_fill(this->model, nodes_amount, branch_radius);

    //смещаем все точки на (+350;-350)
    //move_nodes(tree);
    //добавляем точки и даем им цвет (заполняем nodes)
    nodes_fill(this->model, tree);
    return tr_tree.get()->buildModel(model);
}


#endif // TREE_FACTORY_CPP

#ifndef MODEL_HPP
#define MODEL_HPP

#include "model.h"

Model::Model(const std::vector<Node> nodes, const std::vector<Edge> edges) : \
    nodes(nodes), edges(edges) {
    accuracy = 6;
}

Model::Model(const std::vector<Node> nodes, const std::vector<Edge> edges, const double accuracy) : \
    nodes(nodes), edges(edges), accuracy(accuracy) {}

Model::Model(const Model& model)
{
    this->nodes = model.nodes;
    this->edges = model.edges;
    this->accuracy = model.accuracy;
}

Model::Model(Model&& model)
{
    this->nodes = model.nodes;
    this->edges = model.edges;
    this->accuracy = model.accuracy;
    model.~Model();
}

Model& Model::operator=(const Model& model)
{
    this->nodes = model.nodes;
    this->edges = model.edges;
    this->accuracy = model.accuracy;

    return *this;
}

Model& Model::operator=(Model&& model)
{
    this->nodes = model.nodes;
    this->edges = model.edges;
    this->accuracy = model.accuracy;
    model.~Model();

    return *this;
}

const std::vector<Node> Model::getNodes() const
{
    return this->nodes;
}

const std::vector<Edge> Model::getEdges() const
{
    return this->edges;
}

double Model::getAccuracy() const
{
    return this->accuracy;
}


void Model::addNode(const Node& node)
{
    this->nodes.push_back(node);
}

void Model::addEdge(const Edge& edge)
{
    this->edges.push_back(edge);
}

void Model::setAccuracy(double accuracy)
{
    this->accuracy = accuracy;
}

/*
void Model::shift(const double x, const double y, const double z)
{
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        nodes[i].shift(x, y, z);
    }
}

void Model::scale(const double x, const double y, const double z)
{
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        nodes[i].scale(x, y, z);
    }
}

void Model::rotate(const double x, const double y, const double z)
{
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        nodes[i].rotateX(x);
        nodes[i].rotateY(y);
        nodes[i].rotateZ(z);
    }
}
*/
#endif // MODEL_HPP


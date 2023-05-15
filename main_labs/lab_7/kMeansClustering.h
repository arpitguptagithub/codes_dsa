

#include "points.h"
#include "RedBlackTree.h"
#include <vector>
#include <unordered_map>
#include <cmath>
// #include <iostream>
class cluster : public myRBTree
{// class to represent a cluster
public:
    bool isCentroid;
    Point centroid;

    cluster();
    cluster(Point p);
    void updateCentroid();
};

class GraphPoint : public Point
{// class to represent a point in the graph
public:
    int cluster;

    GraphPoint(Point p, int cluster);
    GraphPoint(int x, int y, int cluster);
    GraphPoint(int x, int y);
    GraphPoint(Point p);

    double calcDist(GraphPoint p)
    {// function to calculate the distance between two points
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }

    bool operator==(const GraphPoint &p) const
    {
        return (x == p.x && y == p.y);
    }

    bool operator!=(const GraphPoint &p) const
    {// function to check if two points are not equal
        return (x != p.x || y != p.y);
    }
};

class my_graph
{
public:// class to represent the graph
    int numClusters;
    int numPoints;
    std::vector<cluster> clusters;
    std::vector<GraphPoint> graphPoints;

    my_graph(int numClusters);
    void setPoints(std::vector<GraphPoint> points);
    void assignRandomCentroids();
    void addPoint(GraphPoint p);
    void removePoint(GraphPoint p);
    void doKMeans();
};


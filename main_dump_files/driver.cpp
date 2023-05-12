#include <iostream>
#include "kMeansClustering.h"

using namespace std;

int main()
{
    my_graph g(3);
    int points[10][2] = {{1, 1}, {-2, 1}, {4, 3}, {5, -4}, {3, 5}, {-3, 4}, {3, 3}, {2, 5}, {1, 4}, {1, 3}};
    for (int i = 0; i < 10; i++)
    {
        g.addPoint(GraphPoint(points[i][0], points[i][1]));
    }
    g.doKMeans();
}
//
#include "kMeansClustering.h"
#include <iostream>
#include <unordered_set>
using namespace std;

//constructor
cluster::cluster()
{
    isCentroid = false;
}

cluster::cluster(Point p)
{
    isCentroid = true;
    centroid = p;
}
// function to update the centroid of the cluster
void cluster::updateCentroid()
{
    // if the cluster is empty, then the centroid is not a centroid
    if (root == nullptr)
    {
        isCentroid = false;
        return;
    }
    // else, the centroid is a centroid
    else
    {
        centroid = Point(sumX / numNodes, sumY / numNodes);
        return;
    }
}

GraphPoint::GraphPoint(Point p, int cluster)
{
    //
    this->x = p.x;
    this->y = p.y;
    this->cluster = cluster;
}

GraphPoint::GraphPoint(int x, int y, int cluster)
{
    this->x = x;
    this->y = y;
    this->cluster = cluster;
}

GraphPoint::GraphPoint(int x, int y)
{
    this->x = x;
    this->y = y;
    this->cluster = -1;
}
// constructor
GraphPoint::GraphPoint(Point p)
{
    this->x = p.x;
    this->y = p.y;
    this->cluster = -1;
}

//constructor for my_graph to initialize the number of clusters 
my_graph::my_graph(int numClusters)
{
    this->numClusters = numClusters;
    numPoints = 0;
    clusters = std::vector<cluster>(numClusters);
    graphPoints = std::vector<GraphPoint>();
}

// function to set the points of the graph
void my_graph::setPoints(std::vector<GraphPoint> points)
{
    graphPoints = points;
    numPoints = points.size();
    assignRandomCentroids();
}

void my_graph::assignRandomCentroids()
{// function to assign random centroids to the clusters
    unordered_set<int> used;
    for (int i = 0; i < numClusters; i++)
    { // loop to assign random centroids to the clusters
        while (true)
        {// loop to assign random centroids to the clusters
            int randNum = rand() % numPoints;
            if (used.find(randNum) == used.end())
            {
                // if the random number is not used, then assign the random number to the cluster
                used.insert(randNum);
                clusters[i] = cluster(graphPoints[randNum]);
                clusters[i].isCentroid = true;
                graphPoints[randNum].cluster = i;
                break;
            }
        }
    }
}

void my_graph::addPoint(GraphPoint p)
{
    graphPoints.push_back(p);
    numPoints++;
}

void my_graph::removePoint(GraphPoint p)
{
    for (int i = 0; i < numPoints; i++)
    {// loop to remove the point from the graph
        if (graphPoints[i] == p)
        {// if the point is found, then remove the point from the graph 
            graphPoints.erase(graphPoints.begin() + i);
            numPoints--;
            return;
        }
    }
}

void my_graph::doKMeans()
{// function to do the k-means clustering   
    for (int i = 0; i < numClusters; i++)
    { // loop to clear the tree and set the centroid to false   
        clusters[i].clearTree();
        clusters[i].isCentroid = false;
    }
    for (auto &p : graphPoints)
    { // loop to set the cluster to -1
        p.cluster = -1;
    }
    assignRandomCentroids();
    bool changed = true;
    while (changed)
    { // loop to do the k-means clustering
        changed = false;
        for (int i = 0; i < numPoints; i++)
        { 
            int minCluster = 0; 
            double minDist = graphPoints[i].calcDist(clusters[0].centroid);
        
            for (int j = 1; j < numClusters; j++)
            { // loop to find the minimum distance
                double dist = graphPoints[i].calcDist(clusters[j].centroid);
                if (dist < minDist)
                {
                    minDist = dist;
                    minCluster = j;
                }
            }
            if (graphPoints[i].cluster != minCluster)
            { // if the cluster is changed, then set the changed to true
                changed = true;
                if (graphPoints[i].cluster != -1)
                {
                    clusters[graphPoints[i].cluster].remove(graphPoints[i]);
                }
                graphPoints[i].cluster = minCluster;
                clusters[minCluster].insert(graphPoints[i]);
            }
        }
        for (int i = 0; i < numClusters; i++)
        {// loop to update the centroid of the cluster
            clusters[i].updateCentroid();
        }
    }
    for (int i = 0; i < numClusters; i++)
    {// loop to print the clusters
        cout << "Cluster " << i << " Centroid: " << clusters[i].centroid.x << ", " << clusters[i].centroid.y << endl;
        clusters[i].print();
        cout << "\n\n";
    }
}

#include<iostream>
#include<climits>
#include<array>
using namespace std;

class Graph {
public:
    int n, m;
    int index; // number of arcs have already added to array
    int** arcs; // declaration 2 dim array
    int* nodes;
    Graph(int n, int m);
    void show();
    void addArcs(int u, int v, int w);
};

int* dijkstra(Graph *graph, int source, int d[]);
array<int, 3> split(string s);
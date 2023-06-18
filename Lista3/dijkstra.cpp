#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <limits>
#include "pqueue.hpp"
#include <fstream>
#include <string>
#include <array>
#include "dijkstra.hpp"

using namespace std;

Graph::Graph(int n, int m)
{
    // Constructor with parameters
    this->n = n; // number of nodes
    this->m = m; // number of arcs
    index = 0;
    arcs = new int *[m]; // declare how many elements have the first dim
    nodes = new int[n];

    int nodesindex = 0;
    for (int i = 0; i < n; i++)
    {
        nodes[i] = nodesindex + 1;
        nodesindex++;
    }

    // clear value in array
    for (int i = 0; i < m; i++)
    {
        arcs[i] = new int[3]; // declare how mamy elements have the second dim
    }
}

void Graph::show()
{
    cout << "mam " << n << " wierzchołkow i " << m << " krawedzi" << endl;
    for (int i = 0; i < m; i++)
    {
        cout << arcs[i][0] << " " << arcs[i][1] << " " << arcs[i][2] << endl;
    }
    for (int i = 0; i < n; i++)
    {
        cout << nodes[i] << " ";
    }
}

void Graph::addArcs(int u, int v, int w)
{
    // u and v is (u,v) acrs, where u is starting node and v in ending node
    if (index < m)
    {
        arcs[index][0] = u;
        arcs[index][1] = v;
        arcs[index][2] = w;
        index++;
    }
}

int *dijkstra(Graph *graph, int source, int d[])
{
    // int d[graph->n + 1];
    int pred[graph->n + 1];

    for (int i = 0; i < graph->n + 1; i++)
    {
        d[i] = numeric_limits<int>::max();
        pred[i] = -1; // undef;
        // (*vertex) = numeric_limits<int>::max();
    }

    d[source] = 0;
    PriorityQueue *Q = new PriorityQueue;
    Q->insert(source, d[source]);

    while (!Q->isEmpty())
    {
        Node *cur = Q->pop();
        for (int i = 0; i < graph->m; i++)
        {
            if (graph->arcs[i][0] == cur->id)
            {
                if (d[graph->arcs[i][1]] > d[cur->id] + graph->arcs[i][2])
                {
                    d[graph->arcs[i][1]] = d[cur->id] + graph->arcs[i][2];
                    pred[graph->arcs[i][1]] = cur->id;
                    Q->insert(graph->arcs[i][1], d[graph->arcs[i][1]]);
                }
            }
        }
    }
}

array<int, 3> split(string s)
{
    string delimiter = " ";
    array<int, 3> array;
    int counter = 0;

    if (s[0] == 'a')
    {
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos)
        {
            token = s.substr(0, pos);
            // cout << token << endl;
            array[counter] = atoi(token.c_str());
            counter++;
            s.erase(0, pos + delimiter.length());
        }
        // cout << s << endl;
        array[counter] = atoi(s.c_str());
    }
    else
    {
        array[0] = 0;
        array[1] = 0;
        array[2] = 0;
    }
    return array;
}

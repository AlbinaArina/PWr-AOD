#include <iostream>
#include <stdio.h>
#include <string>
#include <list>
#include <vector>
using namespace std;

struct buckets {
    list<int> lista;
    int range_a;
    int range_b;
};

class GraphDial {
public:
    int n, m, W;
    int** arcs;
    int index;
    GraphDial(int n, int m);
    void addArcs(int u, int v, int w);
    int idbucket(vector<buckets> B, int s, int range);
    void printcontentofbuckets(vector<buckets> bucketlist, int numberOfBuckets);
    int* dial(int src, int dist[]);
};

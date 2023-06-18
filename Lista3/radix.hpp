#include <iostream>
#include <stdio.h>
#include <string>
#include <list>
#include <vector>
using namespace std;

struct bucketsradix {
    list<int> lista; // wierchołki w bucket
    int range_a;
    int range_b;
};

class GraphRadix {
public:
    int n, m, W;
    int** arcs;
    int index;
    GraphRadix(int n, int m);
    void addArcs(int u, int v, int w);
    int idbucket(vector<bucketsradix> B, int s, int range);
    void printcontentofbuckets(vector<bucketsradix> bucketlist, int numberOfBuckets);
    int* radix(int src, int dist[]);
};
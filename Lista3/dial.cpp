#include <iostream>
#include <stdio.h>
#include <string>
#include <list>
#include <vector>
#include <limits>
#include <math.h>
#include "dial.hpp"
using namespace std;

GraphDial::GraphDial(int n, int m)
{
    this->n = n;
    this->m = m;
    index = 0;
    W = -1;
    arcs = new int *[m];
    for (int i = 0; i < m; i++)
    {
        arcs[i] = new int[3];
    }
}
void GraphDial::addArcs(int u, int v, int w)
{
    if (index < m)
    {
        arcs[index][0] = u;
        arcs[index][1] = v;
        arcs[index][2] = w;
        index++;

        if (w > W)
            W = w;
    }
}
int GraphDial::idbucket(vector<buckets> B, int s, int range)
{
    return s + 1;
}
void GraphDial::printcontentofbuckets(vector<buckets> bucketlist, int numberOfBuckets)
{
    for (int i = 0; i < numberOfBuckets; i++)
    {
        cout << "Bucket numer: " << i << " range(" << bucketlist[i].range_a << ";" << bucketlist[i].range_b << ") ";
        list<int> temp(bucketlist[i].lista.begin(), bucketlist[i].lista.end());
        for (auto j = bucketlist[i].lista.begin(); j != bucketlist[i].lista.end(); j++)
        {
            int t = temp.front();
            cout << t << " ";
            temp.pop_front();
        }
        cout << endl;
    }
}
int *GraphDial::dial(int src, int dist[])
{
    // initialize distance labels
    // int dist[n];
    for (int i = 0; i < n; i++)
    {
        dist[i] = numeric_limits<int>::max();
    }
    dist[src - 1] = 0;

    // init buckets
    int numberOfBuckets = n * W;
    vector<buckets> bucketlist(numberOfBuckets);
    for (int i = 0; i < numberOfBuckets; i++)
    {
        bucketlist[i].range_a = i;
        bucketlist[i].range_b = i;
    }

    // insert nodes into buckets
    bucketlist[0].lista.push_back(src);

    int idx = 0;
    int iterator = 0;

    while (1)
    {
        while (bucketlist[idx].lista.size() == 0 && idx < numberOfBuckets)
        {
            idx++;
        }
        if (idx == numberOfBuckets)
        {
            break;
        }
        // when elements in buckets equals 1 or are more elements but in first bucket, so
        // we can not divide this bucket, so nevermide which element we choose.
        int u = bucketlist[idx].lista.front();
        // cout << "JESTEŚMY W: " << u << endl;
        bucketlist[idx].lista.pop_front();
        for (int i = 0; i < m; i++)
        {
            if (arcs[i][0] == u)
            {
                int v = arcs[i][1];
                int w = arcs[i][2];
                if (dist[v - 1] > dist[u - 1] + w)
                {
                    if (dist[v - 1] != numeric_limits<int>::max())
                    {
                        // cout << "\t\t\ttrzeba przesunąć" << v << endl;
                        int q = v; // idbucket(bucketlist, dist[v-1], numberOfBuckets);
                        // int q = idbucket(bucketlist, dist[v-1], numberOfBuckets);
                        if (q != -1)
                        {
                            bucketlist[q].lista.remove(v);
                        }
                        // printcontentofbuckets(bucketlist, numberOfBuckets);
                    }
                    dist[v - 1] = dist[u - 1] + w;
                    int q = idbucket(bucketlist, dist[v - 1], numberOfBuckets);
                    if (q != -1)
                    {
                        bucketlist[q].lista.push_back(v);
                    }
                }
            }
        }
        iterator++;
        idx = 0;
    }

    return dist;
}
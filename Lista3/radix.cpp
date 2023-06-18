#include <iostream>
#include <stdio.h>
#include <string>
#include <list>
#include <vector>
#include <math.h>
#include <limits>
#include <array>
#include "radix.hpp"

using namespace std;

GraphRadix::GraphRadix(int n, int m)
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
void GraphRadix::addArcs(int u, int v, int w)
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
int GraphRadix::idbucket(vector<bucketsradix> B, int s, int range)
{
    // cout << "szukam miejsca dla" <<  s << endl;
    // for (int i=0; i<range; i++) {
    //         cout << i << " " << B[i].range_a << " " << B[i].range_b << endl;
    // }

    // printcontentofbuckets(B, range);

    int idresult = -1;
    for (int i = 0; i < range; i++)
    {
        if (B[i].range_a <= s && s <= B[i].range_b)
        {
            idresult = i;
            // cout << "znalazlem " << idresult << endl;
            return i;
        }
    }
    // cout << "nie znalazlem " << endl;
    return -1;
}
void GraphRadix::printcontentofbuckets(vector<bucketsradix> bucketlist, int numberOfBuckets)
{
    for (int i = 0; i < numberOfBuckets; i++)
    {
        cout << "Bucket numer: " << i << " range(" << bucketlist[i].range_a << ";" << bucketlist[i].range_b << ") ";
        list<int> temp(bucketlist[i].lista.begin(), bucketlist[i].lista.end());
        for (auto j = bucketlist[i].lista.begin(); j != bucketlist[i].lista.end(); j++)
        {
            // cout << advance(bucketlist[i].lista, 0);
            // cout << "siema";
            int t = temp.front();
            cout << t << " ";
            temp.pop_front();
        }
        cout << endl;
        // cout << "Bucket numer: " << i << " range(" << bucketlist[i].range_a << ";" << bucketlist[i].range_b << ") " << endl;
    }
}
int *GraphRadix::radix(int src, int dist[])
{
    // initialize distance labels
    // int dist[n];
    for (int i = 0; i < n; i++)
    {
        dist[i] = numeric_limits<int>::max();
    }
    dist[src - 1] = 0;

    // init buckets ans theis ranges
    int numberOfBuckets = (int)ceil(log2((float)n * W));
    vector<bucketsradix> bucketlist(numberOfBuckets);
    for (int i = 0; i < numberOfBuckets; i++)
    {
        bucketlist[i].range_a = (int)pow((double)2, (double)i - 1);
        bucketlist[i].range_b = (int)pow((double)2, (double)i) - 1;
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
        // cout << idx << endl;
        if (bucketlist[idx].lista.size() == 1 || idx == 0)
        {
            // when elements in buckets equals 1 or are more elements but in first bucket, so
            // we can not divide this bucket, so nevermide which element we choose.
            int u = bucketlist[idx].lista.front();
            // cout << "JESTEŚMY W: " << u << ":" << dist[u-1] << ":" << idx <<endl;
            // printcontentofbuckets(bucketlist, numberOfBuckets);
            bucketlist[idx].lista.pop_front();
            // cout << "przeszło1" << endl;
            for (int i = 0; i < m; i++)
            {
                if (arcs[i][0] == u)
                {
                    int v = arcs[i][1];
                    int w = arcs[i][2];
                    // cout << "przeszło1.1" << endl;
                    if (dist[v - 1] > dist[u - 1] + w)
                    {
                        // cout << "da" << endl;
                        if (dist[v - 1] != numeric_limits<int>::max())
                        {
                            // cout << "\t\t\ttrzeba przesunąć" << v << endl;
                            int q = idbucket(bucketlist, dist[v - 1], numberOfBuckets);
                            if (q != -1)
                            {
                                // bool x = find(bucketlist[q].lista.begin(), bucketlist[q].lista.end(), v);
                                bucketlist[q].lista.remove(v);
                            }
                            // printcontentofbuckets(bucketlist, numberOfBuckets);
                        }
                        // cout << "przeszło2" << endl;
                        dist[v - 1] = dist[u - 1] + w;
                        int q = idbucket(bucketlist, dist[v - 1], numberOfBuckets);
                        // cout << "przeszło3" << endl;
                        if (q != -1)
                        {
                            bucketlist[q].lista.push_back(v);
                        }
                    }
                }
            }
        }
        else
        {
            // cout << "przeszło4" << endl;
            for (int i = 0; bucketlist[i].range_a < bucketlist[idx].range_a; i++)
            {
                bucketlist[i].range_a = bucketlist[idx].range_a + (int)pow((double)2, (double)i - 1);
                bucketlist[i].range_b = bucketlist[idx].range_a + (int)pow((double)2, (double)i) - 1;
                // bucketlist[idx-1].range_b -= 1;
            }
            // cout << "przeszło5" << endl;
            bucketlist[idx].range_a = -1;
            bucketlist[idx].range_b = -1;

            // cout << "przeszło6" << endl;
            while (bucketlist[idx].lista.size() != 0 && idx < numberOfBuckets)
            {
                // cout << "przeszło6.1" << idx << endl;
                // printcontentofbuckets(bucketlist, numberOfBuckets);
                // NOTE: te dwie linijki poniżej są zle
                int uu = bucketlist[idx].lista.front();
                // cout << "przeszło6.1.2" << endl;
                bucketlist[idx].lista.pop_front();
                // cout << "przeszło6.2" << endl;
                int q = idbucket(bucketlist, dist[uu - 1], numberOfBuckets);
                if (q != -1)
                {
                    bucketlist[q].lista.push_back(uu);
                    // cout << "przeszło6.3" << endl;
                }
            }
            // cout << "przeszło7" << endl;
        }
        iterator++;
        idx = 0;
        // printcontentofbuckets(bucketlist, numberOfBuckets);
        // for (int i=0; i<n; i++) {
        //     cout << dist[i] << " ";
        // }
        // cout << endl;
    }

    // printcontentofbuckets(bucketlist, numberOfBuckets);
    for (int i = 0; i < 6; i++)
    {
        cout << dist[i] << " ";
    }
    cout << endl;

    return dist;
}

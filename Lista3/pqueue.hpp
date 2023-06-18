#include<iostream>
#include<climits>
using namespace std;

class Node {
public:
    int id;
    int cost;
    Node* next;
    Node(int id, int cost);
};


class PriorityQueue {
public:
    Node* root;
    PriorityQueue();
    ~PriorityQueue();
    void insert(int id, int cost);
    Node* pop();
    bool isEmpty();
};
#include <iostream>
#include "pqueue.hpp"

using namespace std;

/** element methods */
Node::Node(int id, int cost) {
    this->id = id;
    this->cost = cost;
    this->next = nullptr;
}

/** priority queue methods */
PriorityQueue::PriorityQueue() {
    this->root = nullptr;
}

void PriorityQueue::insert(int id, int cost) {
    Node* node = new Node(id, cost);
    if (isEmpty() || cost < this->root->cost) {
        node->next = this->root;
        this->root = node;
    } else {
        Node* temp = this->root;
        while (temp->next != nullptr && temp->next->cost <= cost) {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
}

Node* PriorityQueue::pop() {
    if (!isEmpty()) {
        Node* temp = this->root;
        this->root = this->root->next;
        return temp;
    }
    return nullptr;
}

bool PriorityQueue::isEmpty() {
    return this->root == nullptr;
}

PriorityQueue::~PriorityQueue() {
    while (!isEmpty()) {
        Node* temp = pop();
        free(temp);
    }
}
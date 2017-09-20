// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
Tour::Tour()
{
    // TODO: write this member
}

Tour::Tour(Point a, Point b, Point c, Point d)
{
    Node* last = new Node(d);
    first = new Node(a, new Node(b, new Node(c, last)));
    last->next = first;
}

Tour::~Tour()
{
    Node* curNode = first->next;
    Node* temp;
    while(curNode != first){
        temp = curNode;
        curNode = curNode->next;
        delete temp;
        temp = nullptr;
    };
    delete first;
    first = nullptr;
}

void Tour::show()
{
    Node* curNode = first;
    while(true) {
        cout << curNode->point.toString() << endl;
        if (curNode->next == first)
            break;
        else
            curNode = curNode->next;
    }
}

void Tour::draw(QGraphicsScene *scene)
{
    if (first == nullptr)
        return;
    Node* curNode = first;
    while(true) {
        curNode->point.drawTo(curNode->next->point, scene);
        if (curNode->next == first)
            break;
        else
            curNode = curNode->next;
    }
}

int Tour::size()
{
    if (first == nullptr)
        return 0;
    int size = 0;
    Node* curNode = first;
    while(true) {
        size++;
        if(curNode->next == first)
            break;
        else
            curNode = curNode->next;
    }
    return size;
}

double Tour::distance()
{
    if (first == nullptr)
        return 0;
    double dist = 0;
    Node* curNode = first;
    while(true) {
        dist += curNode->point.distanceTo(curNode->next->point);
        if (curNode->next == first)
            break;
        else
            curNode = curNode->next;
    }
    return dist;
}

void Tour::insertNearest(Point p)
{
    if(first != nullptr) {
        double closestDist = first->point.distanceTo(p);
        Node* closestNode = first;
        Node* curNode = first->next;
        while(curNode != first) {
            int curDist = curNode->point.distanceTo(p);
            if (curDist < closestDist) {
                closestDist = curDist;
                closestNode = curNode;
            }
            curNode = curNode->next;
        }

        Node* insert = new Node(p, closestNode->next);
        closestNode->next = insert;

    }

    else {
        first = new Node(p);
        first->next = first;
    }

}

void Tour::insertSmallest(Point p)
{
    if (first != nullptr){
        double bestChange =
                first->point.distanceTo(p) +
                first->next->point.distanceTo(p) -
                first->point.distanceTo(first->next->point);
        Node* bestChangeNode = first;
        Node* curNode = first->next;
        while(curNode != first) {
            double curChange =
                    curNode->point.distanceTo(p) +
                    curNode->next->point.distanceTo(p) -
                    curNode->point.distanceTo(curNode->next->point);
            if (curChange < bestChange) {
                bestChange = curChange;
                bestChangeNode = curNode;

            }
        }

        Node* insert = new Node(p, bestChangeNode->next);
        bestChangeNode->next = insert;
    }
}

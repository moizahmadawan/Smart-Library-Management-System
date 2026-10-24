#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

// ------------------------------------------------------------
// Queue (linked list) - used as the waiting list of a book.
// FIFO: first student who waits gets the book first.
// enqueue / dequeue / pushFront : O(1)
// ------------------------------------------------------------
struct QNode {
    std::string name;
    QNode *next;
};

class Queue {
    QNode *front, *rear;
    int n;

public:
    Queue() : front(nullptr), rear(nullptr), n(0) {}
    ~Queue() { while (!empty()) dequeue(); }

    // Not copyable (owns raw nodes)
    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;

    void enqueue(const std::string &s) {
        QNode *t = new QNode{s, nullptr};
        if (!rear) front = rear = t;
        else { rear->next = t; rear = t; }
        n++;
    }

    // Insert at the front (used by Undo to restore the original order)
    void pushFront(const std::string &s) {
        QNode *t = new QNode{s, front};
        front = t;
        if (!rear) rear = t;
        n++;
    }

    std::string dequeue() {
        if (!front) return "";
        QNode *t = front;
        std::string s = t->name;
        front = front->next;
        if (!front) rear = nullptr;
        delete t;
        n--;
        return s;
    }

    bool empty() const { return n == 0; }
    int size() const { return n; }

    void display() const {
        int i = 1;
        for (QNode *p = front; p; p = p->next)
            std::cout << "      " << i++ << ". " << p->name << "\n";
    }
};

#endif

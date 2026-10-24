#ifndef STACK_H
#define STACK_H

#include <string>

// ------------------------------------------------------------
// Stack (linked list) - stores past actions for Undo.
// LIFO: the last action done is the first one undone.
// push / pop : O(1)
// ------------------------------------------------------------
enum ActionType { ADD_BOOK, ISSUE_BOOK, RETURN_BOOK };

struct Action {
    ActionType type;
    int bookId;
    std::string student;       // who issued / returned
    std::string nextStudent;   // RETURN only: who got auto-issued from the queue
};

struct SNode {
    Action a;
    SNode *next;
};

class Stack {
    SNode *top;

public:
    Stack() : top(nullptr) {}
    ~Stack() { while (!empty()) pop(); }

    Stack(const Stack &) = delete;
    Stack &operator=(const Stack &) = delete;

    void push(const Action &a) { top = new SNode{a, top}; }

    Action pop() {
        SNode *t = top;
        Action a = t->a;
        top = top->next;
        delete t;
        return a;
    }

    bool empty() const { return top == nullptr; }
};

#endif

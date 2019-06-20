#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include<stdlib.h>

template<class T> class ListNode;
template<class T> class LinkedList;

template <class T>
class ListNode{
private:
    T data;
    ListNode<T> *next;
public:
    ListNode(): next(NULL){};
    ListNode(T data_): data(data_), next(NULL){};

    friend class LinkedList<T>;
};

template <class T>
class LinkedList{
private:
    ListNode<T> *first;
public:
    LinkedList<T>(): first(NULL){};
    void print();
    void push_front(T x);
    void push_back(T x);
    void delete_node(T x);
    void clear();
    void reverse();
};
#endif // __LINKEDLIST_H__

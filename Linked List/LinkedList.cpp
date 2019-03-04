#include<iostream>
#include "LinkedList.h"

template<typename T>
void LinkedList<T>::print(){
    if(first == NULL)
        std::cout << "The list is empty!" << std::endl;

    ListNode<T> *current = first;
    while(current)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
void LinkedList<T>::push_front(T data_){
    ListNode<T> *node = new ListNode<T>(data_);
    if(node)
    {
        node->next = first;
        first = node;
    }
    else
        std::cout << "Failed to assign memory to new node!" << std::endl;
}

template<typename T>
void LinkedList<T>::push_back(T data_){
    ListNode<T> *node = new ListNode<T>(data_);
    if(node)
    {
        if(!first)
        {
            first = node;
            return;
        }

        ListNode<T> *tail = first;
        while(tail->next)
            tail = tail->next;
        tail->next = node;
    }
    else
        std::cout << "Failed to assign memory to new node!" << std::endl;
}

template<typename T>
void LinkedList<T>::delete_node(T data_)
{
    ListNode<T> *current = first, *previous = NULL;
    while(current && current->data!=data_)
    {
        previous = current;
        current = current->next;
    }

    if(!current)
        std::cout << "There is no " << data_ << " in list." << std::endl;
    else if(current==first)
    {
        first = first->next;
        delete current;
        current = NULL;
    }
    else
    {
        previous->next = current->next;
        delete current;
        current = NULL;
    }
}

template<typename T>
void LinkedList<T>::clear()
{
    while(first)
    {
        ListNode<T> *current = first;
        first = first->next;
        delete current;
        current = NULL;
    }
}

template<typename T>
void LinkedList<T>::reverse()
{
    if(!first || !first->next)
        return;

    ListNode<T> *previous = NULL, *current = first, *preceding = first->next;

    while(preceding)
    {
        current->next = previous;
        previous = current;
        current = preceding;
        preceding = preceding->next;
    }
    current->next = previous;
    first = current;
}

int main(void)
{
    LinkedList<int> lst;
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);
    lst.push_front(2);
    lst.push_front(1);
    lst.reverse();
    lst.print();
    return 0;
}

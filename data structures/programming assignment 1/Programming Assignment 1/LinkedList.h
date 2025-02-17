#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &rhs);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);
    void mergeNodes(int sourceIndex, int destIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    /* TODO */
    head = NULL;
    size = 0;       
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs)
{   
    /* TODO */
    head = NULL;
    size = 0;
    *this = rhs; 
}

template<class T>
LinkedList<T>::~LinkedList()
{   
    /* TODO */
    while(head != NULL){
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
    if(this == &rhs){
        return *this;
    }
    else {
        this->removeAllNodes();
        Node<T>* temp = rhs.head;
        while (temp != NULL) {
            append(temp->data);
            temp = temp->next;
        }
        return *this;
    } 
}

template<class T>
int LinkedList<T>::getSize() const
{
    /* TODO */
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    /* TODO */
    return head==NULL;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
    if(head == NULL) return false;
    Node<T>* temp = head;
    while(temp) {
        if(temp->data == node->data && temp->prev == node->prev && temp->next == node->next) return true;
        else temp = temp->next;
    }      
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    Node<T>* temp = head;
    if(temp == NULL) return temp;
    while(temp->next!=NULL){
        temp = temp->next;
    } 
    return temp;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    Node<T>* temp = head;
    while(temp){
        if(temp->data != data) {
            temp = temp->next;
        }
        return temp;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
    int i = index;
    Node<T>* temp = head;
    if(index<=size-1){
        while(i!=0){
            temp = temp->next;
            i--;
        }
        return temp;
    }
    return NULL;
}

template<class T>
void LinkedList<T>::append(const T &data)
{   
    /* TODO */
    Node<T>* last = getLastNode();
    if(head == NULL) head = new Node<T>(data);
    else{
        last->next = new Node<T>(data);
        last->next->prev = last;
    }
    size++;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
    if(head == NULL) head = new Node<T>(data);
    else{
        Node<T>* temp = new Node<T>(data);
        temp->next = head;
        head = temp;
        temp->next->prev = temp;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
    Node<T>* temp = head;
    while(temp!=NULL){
        if(node->data == temp->data && node->next == temp->next && node->prev == temp->prev) {
            Node<T>* nodeToAdd = new Node<T>(data, node, node -> next);
            
            if(node->next != NULL)
                node->next->prev = nodeToAdd;
            
            node->next = nodeToAdd;
            size++;
        }
        temp = temp->next;
    }
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    /* TODO */
    int i=index;
    Node<T>* temp = head;
    if(index<=size-1 && 0<=index){
        if(index == 0){
            prepend(data);
        }
        if(i==size-1){
            append(data);
        }
        else{
            while(i!=0){
                temp = temp->next;
                i--;
            }
            temp->next = new Node<T>(data, temp, temp->next);
            temp->next->next->prev = temp->next;
            size++;
        }
    }
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
    Node<T>* temp = head;
    int i = 0;
    while(temp){
        if(temp == node) return i;
        else {
            temp = temp->next;
            i++;
        }
    }
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    /* TODO */
    if(currentIndex == newIndex || currentIndex > size-1 ||newIndex > size-1 || currentIndex<0 || newIndex<0) return;
    Node<T>* curr = getNodeAtIndex(currentIndex);
    Node<T>* location = getNodeAtIndex(newIndex);
    if(currentIndex == 0){
        head = head->next;
        head->prev = NULL;
    }
    curr->next = location->next;
    curr->prev = location;
    location->next = curr;
    if(newIndex != size-1) curr->next->prev = curr;
}

template<class T>
void LinkedList<T>::mergeNodes(int sourceIndex, int destIndex)
{
    /* TODO */
    if(0> sourceIndex || sourceIndex>size-1) {return;}
    if(0> destIndex || destIndex>size-1) {return;}
    else{
        int i=sourceIndex, j=destIndex;
        Node<T>* sourceTemp = head, *destTemp = head;
        while(i>0){
            sourceTemp = sourceTemp->next;
            i--;
        }
        while(j>0){
            destTemp = destTemp->next;
            j--;
        }
        destTemp->data = destTemp->data + sourceTemp->data;
        removeNodeAtIndex(sourceIndex);
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{   
    /* TODO */
    if(head!=NULL){
        if(node == getFirstNode()){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
        }
        else if(node == getLastNode()) {
            Node<T>* temp = getLastNode();
            if(size==1){
                delete temp;
            }
            else{
                temp->prev->next = NULL;
                delete temp;
            }
            size--;
        }
        else{
            Node<T>* travel = head;
            while(travel) {
                if(travel != node) travel = travel->next;
                else{
                    travel->prev->next = travel->next;
                    travel->next->prev = travel->prev;
                    delete travel;
                    size--;
                    return;
                }
            }
        }    
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{   
    /* TODO */
    Node<T>* temp = head;
    while(temp!= NULL){
        if(temp->data != data) temp = temp->next;
        else{ 
            Node<T>* deletion = temp;
            temp = temp->next;
            removeNode(deletion);
        }    
    }
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
    int i = index;
    Node<T>* deletion = head;
    if(index>size-1 || head==NULL || index<0){return;}
    else{
        while(i){
            deletion = deletion->next;
            i--;
        }
        removeNode(deletion);
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{   
    /* TODO */
    while(!isEmpty()){
        removeNode(head);
    } 

}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    while(node)
    {
        std::cout << *node << std::endl;
        node = node->next;
    }

}

#endif //LINKEDLIST_H
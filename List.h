#pragma once
#include <cmath>
#include <stdlib.h>
#include <memory>

template <typename T>
struct Node{
    T data;
    Node *next;
    Node *prev;
};
template <typename T>
class List{
    size_t count;
    size_t index;
    Node<T> *head;
    Node<T> *tail;
    Node<T> *current;
    void goToIndex(int index);
public:
    List();
    ~List();
    void pushFront(T data);
    void popFront();
    void pushBack(T data);
    void popBack();
    void insert(size_t index, T data);
    void remove(size_t index);
    T& operator[](size_t index);
    void clear();
    int size();
    T* toArray();
};

template<typename T>
List<T>::List() {
    count = 0;
    head = tail = current = nullptr;
}

template<typename T>
List<T>::~List() {
    current = tail;
    this->index=count;
    while(count>1){
        current=current->prev;
        delete tail;
        count--;
        this->index--;
        tail=current;
    }
    delete current;
    count--;
    this->index--;
    tail=head=current=nullptr;
}

template<typename T>
void List<T>::pushFront(T data) {
    Node<T> *node = new Node<T>;
    node->data=data;
    node->next = head;
    node->prev = nullptr;
    if(head) head->prev = node; else tail=node;
    head = node;
    current = head;
    this->index=1;
    count++;
}

template<typename T>
void List<T>::popFront() {
    if(head){
        if(!head->next){
            delete head;
            head = tail = current = nullptr;
            this->index=0;
        } else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
            current=head;
            this->index=1;
        }
        count--;
    }
}

template<typename T>
void List<T>::pushBack(T data) {
    Node<T> *node = new Node<T>;
    node->data=data;
    node->next = nullptr;
    node->prev = tail;
    if(tail) tail->next = node; else head = node;
    tail = node;
    count++;
    current=tail;
    this->index=count;
}

template<typename T>
void List<T>::popBack() {
    if(tail){
        if(!tail->prev) {
            delete tail;
            head = tail = current = nullptr;
            this->index=0;
        } else {
            tail=tail->prev;
            delete tail->next;
            tail->next = nullptr;
            current=tail;
            this->index=count-1;
        }
        count--;
    }
}

template<typename T>
void List<T>::insert(size_t index, T data) {
    if(index<=count+1&&index>0){
        if(index==1)pushFront(data); else
        if(index==count+1)pushBack(data); else {
            goToIndex(index);
            Node<T> *node = new Node<T>;
            node->data = data;
            node->next = current;
            node->prev = current->prev;
            current->prev->next = node;
            current->prev = node;
            current = node;
            count++;
        }
    }
}

template<typename T>
void List<T>::remove(size_t index) {
    if(index>0&&index<=count) {
        if (index == 1)popFront(); else
        if (index == count)popBack(); else {
            goToIndex(index);
            current->next->prev = current->prev;
            current->prev->next = current->next;
            delete current;
            current = head;
            this->index = 1;
            count--;
        }
    }
}

template<typename T>
void List<T>::goToIndex(int index) {
    if(index==this->index) return;
    if(index>=1&&index<=count){
        int buf = labs(this->index-index);
         if(index-1<count-index&&index-1<buf){
            current=head;
            this->index=1;
            while(this->index!=index){
                current=current->next;
                this->index++;
            }
        } else if(count-index<buf){
            current=tail;
            this->index=count;
            while (this->index!=index){
                current=current->prev;
                this->index--;
            }
        } else {
            if(this->index>index){
                while(this->index!=index){
                    current=current->prev;
                    this->index--;
                }
            } else {
                while(this->index!=index){
                    current=current->next;
                    this->index++;
                }
            }
        }
    }
}

template<typename T>
T& List<T>::operator[](size_t index) {
    goToIndex(index);
    return (current->data);
}

template<typename T>
void List<T>::clear(){
    current = tail;
    this->index=count;
    while(count>1){
        current=current->prev;
        delete tail;
        count--;
        this->index--;
        tail=current;
    }
    delete current;
    count--;
    this->index--;
    tail=head=current=nullptr;
}

template<typename T>
int List<T>::size() {
    return this->count;
}

template<typename T>
T *List<T>::toArray() {
    T* result = new T[count];
    for(int i = 0; i<count; i++){
        goToIndex(i+1);
        result[i]=current->data;
    }
    return result;
}

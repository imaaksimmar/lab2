#pragma once
#include "exceptions.hpp"

template <typename T>  
class LinkedList {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& val) : value(val), next(nullptr) {} 
    };
    Node* head; 
    int length; 

public:
    LinkedList() : head(nullptr), length(0) {}

    LinkedList(T* items, int count) : head(nullptr), length(0) {
        if(count < 0) {
            throw InvalidArgument();
        }
        if(items == nullptr && count> 0) 
            throw NullPointer();
            
        for(int i=0; i<count; i++) {
            Append(items[i]);  
        }
    }

    LinkedList(const LinkedList<T>& otherLinkedList) : head(nullptr), length(0) {
        Node* current = otherLinkedList.head;
        while(current != nullptr) {
            Append(current->value);  
            current = current->next;
        }
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) { 
        if (this == &other) {
            return *this;
        }

        while(head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }   
        length = 0;
        Node* current = other.head;
        while(current != nullptr) {
            Append(current->value);  
            current = current->next;
        }
        return *this;
    }

    T& operator[](int index) {
        if(index<0 || index>=length) {
            throw IndexOutOfRange();
        }
        Node* current = head;
        for(int i=0; i<index; i++)
            current = current->next;
        return current->value; 
    }

    const T& operator[](int index) const {
        if(index<0 || index>=length) {
            throw IndexOutOfRange();
        }
        Node* current = head;
        for(int i=0; i<index; i++)
            current = current->next;
        return current->value;
    }

    ~LinkedList() {  
        while(head != nullptr) {
            Node* temp = head;      
            head = head->next;    
            delete temp;            
        }
    }

    T GetFirst() const {  
        if(head == nullptr) {
            throw EmptyCollection();
        }
        return head->value;
    }

    T GetLast() const {  
        if(head == nullptr) {  
            throw EmptyCollection();
        }
        Node* current = head;
        while(current->next != nullptr) {  
            current = current->next;
        }
        return current->value;
    }

    T Get(int index) const {  
        if (index < 0 || index >= length) {
            throw IndexOutOfRange();
        }
        Node* current = head;
        for(int i=0; i<index; i++) {  
            current = current->next;
        }
        return current->value;
    }

    int GetLength() const { return length; }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {  
        if (startIndex<0 || endIndex>=length || startIndex>endIndex) {
            throw InvalidArgument();
        }
        
        LinkedList<T>* result = new LinkedList<T>();
        Node* current = head;
        
        for(int i=0; i<startIndex; i++) {
            current = current->next;
        }
   
        for(int i=startIndex; i<=endIndex; i++) {
            result->Append(current->value);
            current = current->next;
        }
        return result;
    }

    
    void Append(T item) {
        Node* newNode = new Node(item);  
        if(head == nullptr) {
            head = newNode;
        } 
        else {
            Node* current = head;
            while(current->next != nullptr) { 
                current = current->next;
            }
            current->next = newNode; 
        }
        length++; 
    }

    void Prepend(T item) {
        Node* newNode = new Node(item);
        newNode->next = head;  
        head = newNode;    
        length++;
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index > length) {
            throw IndexOutOfRange();
        }
        
        if(index == 0) {
            Prepend(item);
            return;
        }
        
        if(index == length) {
            Append(item);
            return;
        }
    
        Node* newNode = new Node(item);
        Node* current = head;
        for(int i=0; i<index-1; i++) {  
            current = current->next;
        }
        newNode->next = current->next;  
        current->next = newNode;        
        length++;
    }

    LinkedList<T>* Concat(LinkedList<T>* otherLinkedList) const { 
        if(otherLinkedList == nullptr) {
            throw NullPointer();
        }
        
        LinkedList<T>* result = new LinkedList<T>();
        
        Node* current = head;
        while(current != nullptr) {
            result->Append(current->value);
            current = current->next;
        }
        
        current = otherLinkedList->head;
        while(current != nullptr) {
            result->Append(current->value);
            current = current->next;
        }
        return result;
    }

};
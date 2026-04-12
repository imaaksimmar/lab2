#pragma once
#include <stdexcept> 

template <typename T>  
class LinkedList {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& val) : value(val), next(nullptr) {} //
    };
    
    Node* head; 
    int length; 

public:
    LinkedList() : head(nullptr), length(0) {}

    LinkedList(T* items, int count) : head(nullptr), length(0) {
        if(count < 0) {
            throw std::invalid_argument("LinkedList: count cannot be negative");
        }
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

    ~LinkedList() {  
        while(head != nullptr) {
            Node* temp = head;      
            head = head->next;    
            delete temp;            
        }
    }


    T GetFirst() const {  
        if(head == nullptr) {
            throw std::out_of_range("LinkedList::GetFirst: list is empty");
        }
        return head->value;
    }

    T GetLast() const {  
        if(head == nullptr) {  
            throw std::out_of_range("LinkedList::GetLast: list is empty");
        }
        Node* current = head;
        while(current->next != nullptr) {  
            current = current->next;
        }
        return current->value;
    }

    T Get(int index) const {  
        if (index < 0 || index >= length) {
            throw std::out_of_range("LinkedList::Get: index out of range");
        }
        Node* current = head;
        for(int i=0; i<index; i++) {  
            current = current->next;
        }
        return current->value;
    }

    int GetLength() const {  
        return length;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {  
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex) {
            throw std::out_of_range("LinkedList::GetSubList: invalid indices");
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
            throw std::out_of_range("LinkedList::InsertAt: index out of range");
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
            throw std::invalid_argument("LinkedList::Concat: otherLinkedList is nullptr");
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
#pragma once
#include "sequence.hpp"
#include "linked_list.hpp"
#include "exceptions.hpp"

template <typename T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T>* list;  
public:
    ListSequence() : list(new LinkedList<T>()) {}
    
    ListSequence(T* items, int count) 
    : list(new LinkedList<T>(items, count)) {}

    ListSequence(const ListSequence<T>& other) 
    : list(new LinkedList<T>(*other.list)) {}  

    ListSequence(const LinkedList<T>& sourceList) 
    : list(new LinkedList<T>(sourceList)) {}

    ~ListSequence() { delete list; }

    ListSequence<T>& operator=(const ListSequence<T>& other) {
    if(this == &other) {
        return *this;  
    }
    delete list;                          
    list = new LinkedList<T>(*other.list); 
    return *this;
    }

    T& operator[](int index) {
        return (*list)[index];  
    }


    T GetFirst() const override { 
        return list->GetFirst();  
    }

    T GetLast() const override {
        return list->GetLast();
    }

    T Get(int index) const override {
        return list->Get(index);
    }

    int GetLength() const override {
        return list->GetLength();
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if(startIndex < 0 || endIndex >= list->GetLength() || startIndex > endIndex) {
            throw InvalidArgument();
        }
        LinkedList<T>* subList = list->GetSubList(startIndex, endIndex);
        ListSequence<T>* result = new ListSequence<T>(*subList);
        delete subList; 
        return result;
    }

    Sequence<T>* Append(T item) override {
        list->Append(item);  
        return this;        
    }

    Sequence<T>* Prepend(T item) override {
        list->Prepend(item);
        return this;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        list->InsertAt(item, index);
        return this;
    }

    Sequence<T>* Concat(Sequence<T>* otherSequence) override {
        if(otherSequence == nullptr) {
            throw NullPointer();
        }
        for(int i=0; i<otherSequence->GetLength(); i++) {
            list->Append(otherSequence->Get(i));
        }
        return this;
    }

    Sequence<T>* Map(T (*func)(T)) const override {
        ListSequence<T>* result = new ListSequence<T>();
        for(int i=0; i<list->GetLength(); i++) {
            result->list->Append(func(list->Get(i)));
        }
        return result;
    }

    Sequence<T>* Where(bool (*predicate)(T)) const override {
        ListSequence<T>* result = new ListSequence<T>();
        for(int i=0; i<list->GetLength(); i++) {
            if(predicate(list->Get(i))) {
                result->list->Append(list->Get(i));
            }
        }
        return result;
    }

    T Reduce(T (*func)(T, T), T initial) const override {
        T result = initial;
        for(int i=0; i<list->GetLength(); i++) {
            result = func(result, list->Get(i));  
        }
        return result;
    }
};
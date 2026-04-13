#pragma once
#include <stdexcept>
#include "sequence.hpp"
#include "linked_list.hpp"

template <typename T>
class ImmutableListSequence : public Sequence<T> {
private:
    LinkedList<T>* list;  
public:
    ImmutableListSequence() : list(new LinkedList<T>()) {}
    ImmutableListSequence(T* items, int count) 
    : list(new LinkedList<T>(items, count)) {}

    ImmutableListSequence(const ImmutableListSequence<T>& other) 
    : list(new LinkedList<T>(*other.list)) {}  

    ImmutableListSequence(const LinkedList<T>& sourceList) 
    : list(new LinkedList<T>(sourceList)) {}

    ~ImmutableListSequence() {
        delete list;  
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
        if(startIndex<0 || endIndex>=list->GetLength() || startIndex>endIndex) {
            throw std::out_of_range("ListSequence::GetSubsequence: invalid indices");
        }
        LinkedList<T>* subList = list->GetSubList(startIndex, endIndex);
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*subList);
        delete subList; 
        return result;
    }

    Sequence<T>* Append(T item) override {
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        copy->list->Append(item); 
        return copy;     
    }

    Sequence<T>* Prepend(T item) override {
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        copy->list->Prepend(item);
        return copy;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if(index<0 || index>list->GetLength()) {
            throw std::out_of_range("ImmutableListSequence::InsertAt: index out of range");
        }
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        copy->list->InsertAt(item, index);
        return copy;
    }

    Sequence<T>* Concat(Sequence<T>* otherSequence) override {
        if(otherSequence == nullptr) {
            throw std::invalid_argument("ListSequence::Concat: otherSequence is nullptr");
        }
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        for(int i=0; i<otherSequence->GetLength(); i++) {
            copy->list->Append(otherSequence->Get(i));
        }
        return copy;
    }

    Sequence<T>* Map(T (*func)(T)) const override {
    ImmutableListSequence<T>* result = new ImmutableListSequence<T>();
    for(int i= 0; i<list->GetLength(); i++) {
        result->list->Append(func(list->Get(i))); 
    }
    return result; 
    }

    Sequence<T>* Where(bool (*predicate)(T)) const override {
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>();
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
#pragma once
#include "sequence.hpp"
#include "dynamic_array.hpp"
#include "linked_list.hpp" 
#include "exceptions.hpp"

template <typename T>
class ImmutableArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* array;

public:
    ImmutableArraySequence() : array(new DynamicArray<T>(0)) {}
    ImmutableArraySequence(T* items, int count) : array(new DynamicArray<T>(items, count)) {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : array(new DynamicArray<T>(*other.array)) {}  
    
    ImmutableArraySequence(const LinkedList<T>& list) 
    : array(new DynamicArray<T>(list.GetLength())) {
        for(int i=0; i<list.GetLength(); i++) {
            array->Set(i, list.Get(i));
        }
    }

    ~ImmutableArraySequence() { delete array; }

    ImmutableArraySequence<T>& operator=(const ImmutableArraySequence<T>& other) {
        if(this == &other) {
            return *this;
        }
        delete array;
        array = new DynamicArray<T>(*other.array);
        return *this;
    }

    T GetFirst() const override { 
        if(array->GetSize() == 0) throw EmptyCollection();
        return array->Get(0);
    }

    T GetLast() const override {
        if(array->GetSize() == 0) throw EmptyCollection();
        return array->Get(array->GetSize()-1);
    }

    T Get(int index) const override {
        if (index < 0 || index >= array->GetSize()) throw IndexOutOfRange();
        return array->Get(index);
    }

    int GetLength() const override { 
        return array->GetSize(); 
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if(startIndex<0 || endIndex>=array->GetSize() || startIndex>endIndex)
            throw InvalidArgument();

        int subSize = endIndex - startIndex + 1;
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>();
        result->array->Resize(subSize); 
        for(int i=0; i<subSize; i++) {
            result->array->Set(i, array->Get(startIndex+i));
        }
        return result;
    }

    template <typename U>
    ImmutableArraySequence<U>* Map(U (*func)(T)) const {
        ImmutableArraySequence<U>* res = new ImmutableArraySequence<U>();
        res->array->Resize(array->GetSize()); 
        for(int i=0; i<array->GetSize(); i++) {
            res->array->Set(i, func(array->Get(i)));
        }
        return res;
    }

    ImmutableArraySequence<T>* Where(bool (*predicate)(T)) const {
    int count = 0;
    for(int i=0; i< array->GetSize(); i++) {
        if(predicate(array->Get(i))) count++;
    }
    ImmutableArraySequence<T>* res = new ImmutableArraySequence<T>();
    res->array->Resize(count);
    int idx = 0;
    for(int i=0; i<array->GetSize(); i++) {
        if(predicate(array->Get(i))) {
            res->array->Set(idx++, array->Get(i));
        }
    }
    return res;
}

    template <typename U>
    U Reduce(U (*func)(U, T), U initial) const {
        U res = initial;
        for(int i=0; i<array->GetSize(); i++) {
            res = func(res, array->Get(i)); 
        }
        return res;
    }
    
    
    Sequence<T>* Append(T item) override {
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        copy->array->Resize(copy->array->GetSize()+ 1);
        copy->array->Set(copy->array->GetSize()-1, item);
        return copy;
    }

    Sequence<T>* Prepend(T item) override {
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        int oldSize = copy->array->GetSize();
        copy->array->Resize(oldSize+1);
        for(int i=oldSize; i>0; i--) {
            copy->array->Set(i, copy->array->Get(i-1));
        }
        copy->array->Set(0, item);
        return copy;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if(index < 0 || index > array->GetSize())
            throw IndexOutOfRange();
        
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        int oldSize = copy->array->GetSize();
        copy->array->Resize(oldSize+ 1);
        for(int i=oldSize; i>index; i--) {
            copy->array->Set(i, copy->array->Get(i-1));
        }
        copy->array->Set(index, item);
        return copy;
    }

    Sequence<T>* Concat(Sequence<T>* otherSequence) override {
        if(otherSequence == nullptr) {
            throw NullPointer();
        }
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);
        int oldSize = copy->array->GetSize();
        int otherSize = otherSequence->GetLength();
        copy->array->Resize(oldSize+otherSize);
        for(int i=0; i<otherSize; i++) {
            copy->array->Set(oldSize+i, otherSequence->Get(i));
        }
        return copy;
    }
};
